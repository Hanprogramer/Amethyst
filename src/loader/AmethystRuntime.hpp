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
#include <platforms/WindowsClientPlatform.hpp>

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
    AmethystRuntime(const AmethystRuntime&);
    AmethystRuntime& operator=(const AmethystRuntime&) = delete;
    static AmethystRuntime* instance;

public:
    AmethystRuntime(std::unique_ptr<Amethyst::Platform> platform);

    static AmethystRuntime& GetInstance()
    {
        if (instance == nullptr) {
            AssertFail("AmethystRuntime was not initialized before use!");
        }

        return *instance;
    }

    void Start();
    void Shutdown();
private:
    void ReadLauncherConfig();
    void LoadModDlls();
    void RunMods();

    //static void ResumeGameThread();
    //static void PauseGameThread();

public:
    Config mLauncherConfig;
    RuntimeContext mAmethystContext;
    bool mRunning = false;
};