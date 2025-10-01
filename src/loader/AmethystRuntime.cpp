#include "loader/AmethystRuntime.hpp"

#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "amethyst/runtime/events/InputEvents.hpp"
#include "amethyst/runtime/interop/RuntimeImporter.hpp"

#include "debug/AmethystDebugging.hpp"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

void AmethystRuntime::Start()
{
    if (mRunning)
        return;

    getContext()->Start();

    // read the config file and load in any mods
    ReadLauncherConfig();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) 
        PromptDebugger();

    // Load all mod DLLs and call their initialize functions
    LoadModDlls(); 
    mRunning = true;
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
    Amethyst::ModLoader& modLoader = *mAmethystContext.mModLoader;

    // Register mod inputs
    // On game start mOptions will be nullptr, but the register inputs event gets called when options is created.
    // When hot-reloading we will have options already so we can register inputs here.
    if (AmethystRuntime::getContext()->mOptions != nullptr) {
        RegisterInputsEvent event(*AmethystRuntime::getInputManager());
        AmethystRuntime::getEventBus()->Invoke(event);
    }

    // Scan the mods directory for mod.json files and load them into the repository
    repository.ScanDirectory(GetAmethystFolder() / "mods", true);

    // Add itself as a mod to the repository to resolve dependencies against
    auto info = Amethyst::Mod::GetInfo(mLauncherConfig.injectedMod);
    
    repository.AddMod(repository.GetMods().cbegin(), info);
    modGraph.SortAndValidate(repository, mLauncherConfig.mods);

    for (const auto& modInfo : modGraph.GetMods()) {
        Log::Info("Resolved '{}'", modInfo->GetVersionedName(), modInfo->UUID);

        if (modInfo->UUID == "00000000-0000-0000-0000-000000000000") {
            Log::Warning("Mod '{}' has the default UUID of '00000000-0000-0000-0000-000000000000' in its mod.json! It is recommended to generate a new one", modInfo->GetVersionedName());
        }
    }

    for (const auto& error : modGraph.GetErrors()) {
        Log::Error("{}", error.toString());
    }

    modLoader.LoadGraph(modGraph);
    for (const auto& error : modLoader.GetErrors()) {
        Log::Error("{}", error.toString());
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
    ResumeGameThread();

    // Listen for hot-reload and keep Amethyst running until the end
    while (true) {
        Sleep(1000 / 20);

        if (GetAsyncKeyState(VK_NUMPAD0) || GetAsyncKeyState(VK_END)) 
            break;
        if ((GetAsyncKeyState('R') & 0x8000) && mRunning == true) {
            Log::Info("\n========================= Starting hot-reload! =========================");

            Shutdown();
            return Start();
        }
    }
}

void AmethystRuntime::Shutdown()
{
    if (!mRunning)
        return;

    BeforeModShutdownEvent shutdownEvent;
    getEventBus()->ReverseInvoke(shutdownEvent);

    // Clear lists of mods & functions.
    getContext()->Shutdown();
    mRunning = false;
}

void AmethystRuntime::ResumeGameThread()
{
    typedef NTSTATUS(NTAPI* NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(gMcThreadHandle, NULL);

    Log::Info("Resumed game thread!");
}

void AmethystRuntime::PauseGameThread()
{
    typedef NTSTATUS(NTAPI* NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(gMcThreadHandle, NULL);

    Log::Info("Paused game thread!");
}

extern "C" __declspec(dllexport) 
AmethystContext* GetContextInstance()
{
    return AmethystRuntime::getContext();
}
