#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "amethyst/Log.hpp"

#include "loader/AmethystRuntime.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
DWORD WINAPI Main();
DWORD __stdcall EjectThread(LPVOID lpParameter);

extern "C" __declspec(dllexport) void __cdecl Init(DWORD dMcThreadID, HANDLE hMcThreadHandle);

extern "C" __declspec(dllexport) DWORD __cdecl ServerInit(LPVOID lp);

LONG WINAPI AmethystUnhandledExceptionsHandler(EXCEPTION_POINTERS* ExceptionInfo);