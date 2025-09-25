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
#include "hooks/RenderingHooks.hpp"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

void AmethystRuntime::Start()
{
    getContext()->Start();
    Log::Info("Using 'AmethystRuntime@{}'", MOD_VERSION);

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
        Log::Info("Minecraft Version: {}.{}.{}", version.mMajor, version.mMinor, version.mPatch);
    }

    // read the config file and load in any mods
    ReadLauncherConfig();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) 
        PromptDebugger();

    // Initialize our runtime importer
    mAmethystMod.GetRuntimeImporter().Initialize();

    // Add our resources before loading mods
    AddOwnResources();

    // Create our hooks
    CreateOwnHooks();

    // Load all mod DLLs and call their initialize functions
    LoadModDlls(); 
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
    mAmethystContext.mModRegistry->ScanForMods(&mAmethystMod);
    for (auto& info : mAmethystContext.mModRegistry->GetModsToLoad(mLauncherConfig.mods, &mAmethystMod)) {
        mAmethystContext.mMods.emplace_back(*info);
    }

    for (const auto& error : mAmethystContext.mModRegistry->GetErrors()) {
        std::string errorType;
        switch (error.type) {
            case Amethyst::ModRegistry::Error::Type::DependencyFailed:
                errorType = "DependencyFailed";
                break;
            case Amethyst::ModRegistry::Error::Type::MissingDependency:
                errorType = "MissingDependency";
                break;
            case Amethyst::ModRegistry::Error::Type::CircularDependency:
                errorType = "CircularDependency";
                break;
            default:
                errorType = "Unknown";
                break;
        }
        Log::Error("Failed to load mod '{}': {} (type: {})", error.uuid, error.message, errorType);
        if (!error.data.empty()) {
            Log::Error("  Additional Info:");
            for (const auto& info : error.data) {
                Log::Error("    - {}", info);
            }
        }
    }

    // Add packs for each mod and load all mod functions
    for (auto& mod : mAmethystContext.mMods) {
        auto versionedName = mod.mInfo.GetVersionedName();
        Log::Info("Loading '{}'", versionedName);
        mod.Load();

        // Check if the mod has a resource pack and register it if it does
        if (fs::exists(fs::path(GetAmethystFolder() / "mods" / versionedName / "resource_packs" / "main_rp" / "manifest.json")))
            mAmethystContext.mPackManager->RegisterNewPack(&mod, "main_rp", PackType::Resources);
        
        // Check if the mod has a behavior pack and register it if it does
        if (fs::exists(fs::path(GetAmethystFolder() / "mods" / versionedName / "behavior_packs" / "main_bp" / "manifest.json")))
            mAmethystContext.mPackManager->RegisterNewPack(&mod, "main_bp", PackType::Behavior);

        _LoadModFunc(mModInitialize, mod, "Initialize");
    }

    // Invoke mods to initialize and setup hooks, etc..
    for (auto& [mod, initialize] : mModInitialize)
        initialize(&mAmethystContext, mod);

    // Allow mods to add listeners to eachothers events
    AddModEventListenersEvent event;
    AmethystRuntime::getEventBus()->Invoke<AddModEventListenersEvent>(event);
}

template <typename T>
void AmethystRuntime::_LoadModFunc(std::unordered_map<Amethyst::Mod*, T>& map, Amethyst::Mod& mod, const char* functionName)
{
    FARPROC address = mod.GetFunction(functionName);
    if (address == NULL) return;
    map[&mod] = reinterpret_cast<T>(address);
}

void AmethystRuntime::PromptDebugger()
{
    Log::Info("Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void AmethystRuntime::AddOwnResources()
{
    // Add our own resource pack
    mAmethystContext.mPackManager->RegisterNewPack(&mAmethystMod, "main_rp", PackType::Resources, Amethyst::PackPriority::Lowest);
}

void AmethystRuntime::CreateOwnHooks()
{
    Amethyst::InitializeAmethystMod(*getContext(), mAmethystMod);

    CreateInputHooks();
    CreateResourceHooks();
    CreateStartScreenHooks();
    CreateModFunctionHooks();
    CreateNetworkingHooks();
    CreateUIHooks();
    CreateItemHooks();
    CreateRenderingHooks();
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

    // Clear lists of mods & functions.
    mModInitialize.clear();
    mAmethystContext.mMods.clear();

    // Shutdown our runtime importer
    mAmethystMod.GetRuntimeImporter().Shutdown();
}

void AmethystRuntime::ResumeGameThread()
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(gMcThreadHandle, NULL);

    Log::Info("Resumed game thread!");
}

void AmethystRuntime::PauseGameThread()
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(gMcThreadHandle, NULL);

    Log::Info("Paused game thread!");
}

extern "C" __declspec(dllexport) AmethystContext* GetContextInstance()
{
    return AmethystRuntime::getContext();
}
