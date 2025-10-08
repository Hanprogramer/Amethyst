#include "dllmain.hpp"
#include "debug/AmethystDebugging.hpp"
#include "amethyst/runtime/ModContext.hpp"

HMODULE hModule;
HANDLE gMcThreadHandle;
DWORD gMcThreadId;

extern AmethystContext* _AmethystContextInstance;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    ::hModule = hModule;
    return TRUE;
}

DWORD WINAPI Main()
{
    auto windowsClientPlatform = std::make_unique<WindowsClientPlatform>(gMcThreadHandle);
    AmethystRuntime* runtime = new AmethystRuntime(std::move(windowsClientPlatform));

    // Initialize AmethystContextInstance so Amethyst::GetXYZ functions work.
    _AmethystContextInstance = &runtime->mAmethystContext;

    auto& platform = Amethyst::GetPlatform();
    platform.Initialize(); // Initialize things like uncaught exception handling
    platform.InitializeConsole(); // Initialize Amethyst Logging

    try {
        runtime->Start();
    }
    catch (std::exception& exception) {
        Log::Error("Uncaught Exception: {}", exception.what());
        throw exception;
    }

    platform.ShutdownWaitForInput();
    return 0;
}

void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle)
{
    // Define a struct to hold the data
    struct ThreadData {
        DWORD dwThreadId;
        HANDLE hThreadHandle;
    };

    // Create an instance of the ThreadData struct
    ThreadData* pData = new ThreadData;
    pData->dwThreadId = dMcThreadID;
    pData->hThreadHandle = hMcThreadHandle;

    auto mainCallLambda = [](LPVOID lpParameter) -> DWORD {
        // Cast the parameter back to ThreadData
        auto pData = static_cast<ThreadData*>(lpParameter);
        gMcThreadHandle = pData->hThreadHandle;
        gMcThreadId = pData->dwThreadId;

        DWORD result = Main();

        // Return the result
        delete pData;
        return result;
    };

    // Create the thread and pass the lambda function and the ThreadData struct
    CreateThread(nullptr, 0, mainCallLambda, pData, 0, nullptr);
}
