#pragma once
#include "hooks/Hooks.hpp"
#include "hooks/InputHooks.hpp"
#include "hooks/ResourceHooks.hpp"
#include <amethyst/Config.hpp>
#include <amethyst/Log.hpp>
#include <amethyst/MinecraftVtables.hpp>
#include <amethyst/runtime/AmethystContext.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <minecraft/src/common/world/item/Item.hpp>
#include <vector>
#include <RuntimeContext.hpp>

namespace fs = std::filesystem;

typedef void (*ModInitialize)(AmethystContext* context, const Amethyst::Mod* mod);
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
    AmethystRuntime() : 
        mAmethystMod(Amethyst::Mod::GetInfo(std::format("AmethystRuntime@{}", MOD_VERSION)))
    {
        mAmethystMod.Attach(::hModule);
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

    static std::vector<Amethyst::Mod>& getMods()
    {
        return AmethystRuntime::getInstance()->mAmethystContext.mMods;
    }

    static Amethyst::MinecraftPackageInfo* getMinecraftPackageInfo()
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mPackageInfo;
    }

    static Amethyst::RuntimeImporter* getRuntimeImporter() 
    {
        return &AmethystRuntime::getInstance()->mAmethystMod.GetRuntimeImporter();
    }

    static Amethyst::Mod* getAmethystMod() 
    {
        return &AmethystRuntime::getInstance()->mAmethystMod;
    }

    void Start();
    void Shutdown();

    static void PromptDebugger();
private:
    void ReadLauncherConfig();
    void LoadModDlls();
    void AddOwnResources();
    void CreateOwnHooks();
    void RunMods();
    void ResumeGameThread();
    void PauseGameThread();

    template <typename T>
    void _LoadModFunc(std::unordered_map<Amethyst::Mod*, T>& map, Amethyst::Mod& mod, const char* functionName);

private:
    Config mLauncherConfig;
    RuntimeContext mAmethystContext;

public:
    std::unordered_map<Amethyst::Mod*, ModInitialize> mModInitialize;
    Amethyst::Mod mAmethystMod;
};