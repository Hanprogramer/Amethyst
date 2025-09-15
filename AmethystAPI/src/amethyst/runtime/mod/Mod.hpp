#pragma once
#include "Json.hpp"
#include <Windows.h>
#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>
#include <amethyst/runtime/interop/RuntimeImporter.hpp>
using json = nlohmann::json;

namespace fs = std::filesystem;

class Mod {
    friend class AmethystRuntime;

private:
    HMODULE hModule = nullptr;
    std::unique_ptr<Amethyst::RuntimeImporter> mRuntimeImporter = nullptr;

public:
    struct Metadata {
        std::string name;
        std::string version;
        std::vector<std::string> author;

        std::string GetVersionedName() const {
            return name + "@" + version;
        }
    };

public:
    std::string modName;
    Metadata metadata;

public:
    Mod(std::string modName);
    FARPROC GetFunction(const char* functionName);
    HMODULE GetModule() const;
    Amethyst::RuntimeImporter& GetRuntimeImporter() const;
    void Shutdown();

public:
    static Mod::Metadata GetMetadata(std::string modName);
    static Mod::Metadata ParseMetadata(std::string modName, std::string fileContents);

private:
    fs::path GetTempDll();
};