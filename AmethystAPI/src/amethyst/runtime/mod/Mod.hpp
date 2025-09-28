#pragma once
#include "Json.hpp"
#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>
#include <amethyst/runtime/interop/RuntimeImporter.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using json = nlohmann::json;

namespace fs = std::filesystem;

class Mod {
    friend class AmethystRuntime;

private:
    HMODULE hModule = nullptr;
    std::unique_ptr<Amethyst::RuntimeImporter> mRuntimeImporter = nullptr;

public:
    struct Metadata {
        std::string modNamespace;
        std::string name;
        std::string logName;
        std::string friendlyName;
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
    FARPROC GetFunction(const char* functionName) const;
    HMODULE GetModule() const;
    Amethyst::RuntimeImporter& GetRuntimeImporter() const;
    void Shutdown();

    bool operator==(const Mod& other) const {
        return metadata.modNamespace == other.metadata.modNamespace && metadata.version == other.metadata.version;
    }

public:
    static Mod::Metadata GetMetadata(std::string modName);
    static Mod::Metadata ParseMetadata(std::string modName, std::string fileContents);

private:
    fs::path GetTempDll();
};

namespace std {
    template<>
    struct hash<Mod> {
        std::size_t operator()(const Mod& s) const noexcept
        {
            std::size_t h1 = std::hash<std::string>{}(s.metadata.modNamespace);
            std::size_t h2 = std::hash<std::string>{}(s.metadata.name);
            return h1 ^ (h2 << 1);
        }
    };
}