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
#include "amethyst/runtime/ModContext.hpp"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

extern "C" __declspec(dllexport)
void Initialize(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Amethyst::InitializeAmethystMod(ctx, mod);
    Log::Info("Initializing runtime mod: '{}'", mod.mInfo->GetVersionedName());
    SemVersion version = ctx.mPackageInfo.mVersion;

    if (version.mMajor != MOD_TARGET_VERSION_MAJOR || version.mMinor != MOD_TARGET_VERSION_MINOR || version.mPatch != MOD_TARGET_VERSION_PATCH) {
        Log::Warning("{} has been made for Minecraft version {}.{}.{}, detected version {}.{}.{}\n\t> It should be expected that things may break on this version.\n\t> We will not provide support for unintended versions.",
            mod.mInfo->GetVersionedName(),
            MOD_TARGET_VERSION_MAJOR, MOD_TARGET_VERSION_MINOR, MOD_TARGET_VERSION_PATCH,
            version.mMajor, version.mMinor, version.mPatch
        );
    }
    else {
        Log::Info("Minecraft Version: {}.{}.{}", version.mMajor, version.mMinor, version.mPatch);
    }

    CreateInputHooks();
    CreateResourceHooks();
    CreateStartScreenHooks();
    CreateModFunctionHooks();
    CreateNetworkingHooks();
    CreateUIHooks();
    CreateItemHooks();
    CreateRenderingHooks();
}

extern "C" __declspec(dllexport)
void Shutdown(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Log::Info("Shutting down runtime mod: '{}'", mod.mInfo->GetVersionedName());
    Amethyst::ResetAmethystMod();
}

void AmethystRuntime::Start()
{
    getContext()->Start();

    // read the config file and load in any mods
    ReadLauncherConfig();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) 
        PromptDebugger();

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
    mLauncherConfig.mods.insert(mLauncherConfig.mods.begin(), mLauncherConfig.injectedMod);
}

void AmethystRuntime::LoadModDlls()
{
    Amethyst::ModRepository& repository = *mAmethystContext.mModRepository;
    Amethyst::ModGraph& modGraph = *mAmethystContext.mModGraph;

    // Scan the mods directory for mod.json files and load them into the repository
    repository.ScanDirectory(GetAmethystFolder() / "mods", true);

    // Add itself as a mod to the repository to resolve dependencies against
    auto info = Amethyst::Mod::GetInfo(mLauncherConfig.injectedMod);
    repository.AddMod(repository.GetMods().cbegin(), info);

    modGraph.SortAndValidate(repository, mLauncherConfig.mods);
    for (const auto& modInfo : modGraph.GetMods()) {
        Log::Info("Resolved '{}'", modInfo->GetVersionedName(), modInfo->UUID);
    }

    for (const auto& error : modGraph.GetErrors()) {
        Log::Error("{}", error.toString());
    }

    for (const auto& info : modGraph.GetMods()) {
        mAmethystContext.mMods.emplace_back(info);
    }

    // Add packs for each mod and load all mod functions
    for (auto& mod : mAmethystContext.mMods) {
        auto versionedName = mod.mInfo->GetVersionedName();
        Log::Info("Loading '{}'", versionedName, mod.mInfo->UUID);
        mod.Load();
        mod.CallInitialize(*getContext(), mod);
    }

    // Allow mods to add listeners to eachothers events
    AddModEventListenersEvent event;
    AmethystRuntime::getEventBus()->Invoke<AddModEventListenersEvent>(event);
}

void AmethystRuntime::PromptDebugger()
{
    Log::Info("Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
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

    for (auto& mod : mAmethystContext.mMods) {
        mod.CallShutdown(*getContext(), mod);
    }

    // Clear lists of mods & functions.
    getContext()->Shutdown();

    mAmethystContext.mMods.clear();
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

extern "C" __declspec(dllexport) 
AmethystContext* GetContextInstance()
{
    return AmethystRuntime::getContext();
}
