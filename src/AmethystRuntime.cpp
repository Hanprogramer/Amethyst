#include "AmethystRuntime.hpp"
#include "debug/AmethystDebugging.hpp"
#include <amethyst/runtime/events/ModEvents.hpp>
#include <amethyst/runtime/events/InputEvents.hpp>
#include <amethyst/runtime/interop/RuntimeImporter.hpp>
#include <amethyst/Log.hpp>
#include <format>
#include "hooks/NetworkingHooks.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "hooks/ui/UIHooks.hpp"
#include "hooks/item/ItemHooks.hpp"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

void AmethystRuntime::Start()
{
    getContext()->Start();
    Log::Info("[AmethystRuntime] Using 'AmethystRuntime@{}'", MOD_VERSION);

    SemVersion version = getMinecraftPackageInfo()->mVersion;

    if (version.mMajor != MOD_TARGET_VERSION_MAJOR || version.mMinor != MOD_TARGET_VERSION_MINOR || version.mPatch != MOD_TARGET_VERSION_PATCH) 
    {
        Log::Warning("\nAmethystRuntime@{} has been made for Minecraft version {}.{}.{}, detected version {}.{}.{}\n\t> It should be expected that things may break on this version.\n\t> We will not provide support for unintended versions.\n", 
            MOD_VERSION, 
            MOD_TARGET_VERSION_MAJOR, MOD_TARGET_VERSION_MINOR, MOD_TARGET_VERSION_PATCH,
            version.mMajor, version.mMinor, version.mPatch
        );
    }
    else {
        Log::Info("[AmethystRuntime] Minecraft Version: {}.{}.{}", version.mMajor, version.mMinor, version.mPatch);
    }

    // read the config file and load in any mods
    ReadLauncherConfig();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) 
        PromptDebugger();

    // Initialize our runtime importer
    mRuntimeImporter->Initialize();

    // Add our resources before loading mods
    AddOwnResources();
    LoadModDlls(); 

    // Create our hooks then run the mods
    CreateOwnHooks();
    RunMods();

} 

void AmethystRuntime::ReadLauncherConfig()
{
    // Ensure it exists
    fs::path launcherConfigPath = GetAmethystFolder() / "launcher_config.json";

    if (!fs::exists(launcherConfigPath)) {
        throw std::exception("launcher_config.json could not be found!");
    }

    // Try to read it to a std::string
    std::ifstream configFile(launcherConfigPath);
    if (!configFile.is_open()) {
        throw std::exception("Failed to open launcher_config.json");
    }

    // Read into a std::string
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();
    std::string fileContents = buffer.str();

    mLauncherConfig = Config(fileContents);
}

void AmethystRuntime::LoadModDlls()
{
    // Load all mods from the launcher_config.json
    for (auto& modName : mLauncherConfig.mods) {
        mAmethystContext.mMods.emplace_back(modName);
    }

    // Add packs for each mod and load all mod functions
    for (auto& mod : mAmethystContext.mMods) {
        Log::Info("[AmethystRuntime] Loading '{}'", mod.modName);

        // Check if the mod has a resource pack and register it if it does
        if (fs::exists(fs::path(GetAmethystFolder() / "mods" / mod.modName / "resource_packs" / "main_rp" / "manifest.json")))
            mAmethystContext.mPackManager->RegisterNewPack(mod.metadata, "main_rp", PackType::Resources);
        
        // Check if the mod has a behavior pack and register it if it does
        if (fs::exists(fs::path(GetAmethystFolder() / "mods" / mod.modName / "behavior_packs" / "main_bp" / "manifest.json")))
            mAmethystContext.mPackManager->RegisterNewPack(mod.metadata, "main_bp", PackType::Behavior);
        
        // Create runtime importer instance and initialize it
        mod.mRuntimeImporter = std::make_unique<Amethyst::RuntimeImporter>(mod.GetModule());
        mod.GetRuntimeImporter().Initialize();

        _LoadModFunc(&mModInitialize, mod, "Initialize");
    }

    // Invoke mods to initialize and setup hooks, etc..
    for (auto& modInitialize : mModInitialize)
        modInitialize(&mAmethystContext);

    // Allow mods to add listeners to eachothers events
    AddModEventListenersEvent event;
    AmethystRuntime::getEventBus()->Invoke<AddModEventListenersEvent>(event);
}

template <typename T>
void AmethystRuntime::_LoadModFunc(std::vector<T>* vector, Mod& mod, const char* functionName)
{
    FARPROC address = mod.GetFunction(functionName);
    if (address == NULL) return;
    vector->push_back(reinterpret_cast<T>(address));
}

void AmethystRuntime::PromptDebugger()
{
    Log::Info("[AmethystRuntime] Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void AmethystRuntime::AddOwnResources()
{
    // Add our own resource pack
    mAmethystContext.mPackManager->RegisterNewPack({ "AmethystRuntime", MOD_VERSION, { "FrederoxDev" }}, "main_rp", PackType::Resources);
}

void AmethystRuntime::CreateOwnHooks()
{
    Amethyst::InitializeAmethystMod(*getContext());

    CreateInputHooks();
    CreateResourceHooks();
    CreateStartScreenHooks();
    CreateModFunctionHooks();
    CreateNetworkingHooks();
    CreateUIHooks();
    CreateItemHooks();
}

void AmethystRuntime::RunMods()
{
    // Register mod inputs
    // On game start mOptions will be nullptr, but the register inputs event gets called when options is created.
    // When hot-reloading we will have options already so we can register inputs here.
    if (AmethystRuntime::getContext()->mOptions != nullptr) {
        RegisterInputsEvent event(*AmethystRuntime::getInputManager());
        AmethystRuntime::getEventBus()->Invoke(event);
    }

    ResumeGameThread();

    // Listen for hot-reload and keep Amethyst running until the end
    while (true) {
        Sleep(1000 / 20);

        if (GetAsyncKeyState(VK_NUMPAD0)) break;
        if (GetAsyncKeyState('R') & 0x8000) {
            Log::Info("\n========================= Beginning hot-reload! =========================");

            Shutdown();
            return Start();
        }
    }
}

void AmethystRuntime::Shutdown()
{
    BeforeModShutdownEvent shutdownEvent;
    getEventBus()->Invoke(shutdownEvent);
    getContext()->Shutdown();

    // Unload all mod dll's.
    for (auto& mod : mAmethystContext.mMods) {
        mod.Shutdown();
    }

    // Clear lists of mods & functions.
    mAmethystContext.mMods.clear();
    mModInitialize.clear();

    // Shutdown our runtime importer
    mRuntimeImporter->Shutdown();
}

void AmethystRuntime::ResumeGameThread()
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(gMcThreadHandle, NULL);

    Log::Info("[AmethystRuntime] Resumed game thread (0x{:x}) 0x{:x}", gMcThreadId, (uint64_t)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread"));
}

void AmethystRuntime::PauseGameThread()
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(gMcThreadHandle, NULL);

    Log::Info("[AmethystRuntime] Paused game thread (0x{:x})", gMcThreadId);
}

extern "C" __declspec(dllexport) AmethystContext* GetContextInstance()
{
    return AmethystRuntime::getContext();
}