#include "platforms/WindowsPlatformCommon.hpp"
#include <amethyst/Memory.hpp>
#include <debug/AmethystDebugging.hpp>
#include "loader/dllmain.hpp"
#include <amethyst/runtime/ModContext.hpp>

WindowsPlatformCommon::WindowsPlatformCommon(HANDLE mcThreadHandle)
    : mMcThreadHandle(mcThreadHandle) {}

void WindowsPlatformCommon::AttachDebugger() const
{
    Log::Info("Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void WindowsPlatformCommon::PauseGameThread() const
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(mMcThreadHandle, NULL);
    Log::Info("Paused game thread!");
}

void WindowsPlatformCommon::ResumeGameThread() const
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(mMcThreadHandle, NULL);
    Log::Info("Resumed game thread!");
}

void WindowsPlatformCommon::InitializeConsole() const
{
    // The logger really needs to be platform independant
    // and it would be good if it supported writing to a file
    Log::InitializeConsole();
}

LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo == nullptr) {
        std::cerr << "ExceptionInfo is nullptr" << std::endl;
        return ExceptionContinueSearch;
    }

    HMODULE hModule = GetModuleHandle(nullptr);

    TCHAR szModuleName[MAX_PATH];
    GetModuleFileName(hModule, szModuleName, MAX_PATH);

    EXCEPTION_RECORD* exceptionRecord = ExceptionInfo->ExceptionRecord;
    uint64_t exceptionAddr = (uint64_t)exceptionRecord->ExceptionAddress;
    uint64_t exceptionCode = (uint64_t)exceptionRecord->ExceptionCode;

    Log::Error("Exception thrown at 0x{:x}\n", exceptionAddr - GetMinecraftBaseAddress(), szModuleName);
    LogAssemblyOfExceptionCause(exceptionAddr);
    Log::Error("\nError Code: 0x{:x}", exceptionCode);

    auto& platform = Amethyst::GetPlatform();
    platform.ShutdownWaitForInput();
    return ExceptionContinueSearch;
}

void WindowsPlatformCommon::Initialize()
{
    SetUnhandledExceptionFilter(AmethystUnhandledExceptionsHandler);
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    ExitProcess(0);
}

void WindowsPlatformCommon::Shutdown()
{
    auto& rt = AmethystRuntime::GetInstance();
    rt.Shutdown();

    Log::DestroyConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void WindowsPlatformCommon::ShutdownWaitForInput()
{
    Log::Info("Press Numpad0/End to close...");

    while (1) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
}

bool WindowsPlatformCommon::HasRequestedStop() const
{
    return GetAsyncKeyState(VK_NUMPAD0) || GetAsyncKeyState(VK_END);
}

bool WindowsPlatformCommon::HasRequestedHotReload() const
{
    return GetAsyncKeyState('R') & 0x8000;
}