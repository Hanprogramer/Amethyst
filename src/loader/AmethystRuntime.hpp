#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <format>

#include "amethyst/Log.hpp"
#include "amethyst/Config.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include "mc/src/common/world/item/Item.hpp"

#include "loader/RuntimeContext.hpp"

namespace fs = std::filesystem;
extern HMODULE hModule;

/*
 Entry:
 - Initialize console

 Hot-reloading:
 - Initialize MinHook
 - Load mod Dlls and find any mod functions
 - Create hooks that are time dependant
 - If dev mode, prompt a debugger
 - Create regular hooks then call all loaded mods initialize functions
*/
class AmethystRuntime {
private:
    // AmethystRuntime is a Singleton so don't allow creating from outside
    AmethystRuntime()
    {
    }

    AmethystRuntime(const AmethystRuntime&);
    AmethystRuntime& operator=(const AmethystRuntime&) = delete;
    static AmethystRuntime* instance;

public:
    static AmethystRuntime* getInstance()
    {
        if (instance == nullptr) instance = new AmethystRuntime();
        return instance;
    }

    static AmethystContext* getContext() 
    {
        return &AmethystRuntime::getInstance()->mAmethystContext;
    }

    static Amethyst::HookManager* getHookManager()
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mHookManager.get();
    }

    static Amethyst::EventBus* getEventBus() 
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mEventBus.get();
    }

    static Amethyst::InputManager* getInputManager() 
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mInputManager.get();
    }

    static Amethyst::PatchManager* getPatchManager() 
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mPatchManager.get();
    }

    static Amethyst::EnumAllocator* getEnumAllocator()
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mEnumAllocator.get();
    }

    static Amethyst::MinecraftPackageInfo* getMinecraftPackageInfo()
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mPackageInfo;
    }

    void Start();
    void Shutdown();

    static void PromptDebugger();
private:
    void ReadLauncherConfig();
    void LoadModDlls();
    void RunMods();

    static void ResumeGameThread();
    static void PauseGameThread();

private:
    Config mLauncherConfig;
    RuntimeContext mAmethystContext;
    bool mRunning = false;
};