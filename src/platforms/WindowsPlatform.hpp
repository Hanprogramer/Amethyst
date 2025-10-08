#pragma once
#include <amethyst/runtime/platform/Platform.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

// base class for anything windows, things can be further specialized for server/client if needed

class WindowsPlatform : public Amethyst::Platform {
public:
    WindowsPlatform(HANDLE mcThreadHandle);

    virtual void AttachDebugger() const override;
    virtual void PauseGameThread() const override;
    virtual void ResumeGameThread() const override;
    virtual void InitializeConsole() const override;

private:
    HANDLE mMcThreadHandle;
};