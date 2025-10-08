#include "WindowsPlatform.hpp"
#include <amethyst/Memory.hpp>

WindowsPlatform::WindowsPlatform(HANDLE mcThreadHandle)
    : mMcThreadHandle(mcThreadHandle) {}

void WindowsPlatform::AttachDebugger() const
{
    Log::Info("Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = std::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void WindowsPlatform::PauseGameThread() const
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(mMcThreadHandle, NULL);
    Log::Info("Paused game thread!");
}

void WindowsPlatform::ResumeGameThread() const
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(mMcThreadHandle, NULL);
    Log::Info("Resumed game thread!");
}

void WindowsPlatform::InitializeConsole() const
{
    // The logger really needs to be platform independant
    // and it would be good if it supported writing to a file
    Log::InitializeConsole();
}
