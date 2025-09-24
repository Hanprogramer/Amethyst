#pragma once
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>

#include "Json.hpp"

#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
#include <amethyst/runtime/mod/ModInfo.hpp>
#include <amethyst/runtime/mod/ModuleHandle.hpp>
#include <amethyst/runtime/interop/RuntimeImporter.hpp>

namespace fs = std::filesystem;

namespace Amethyst {
class Mod {
public:
    using Info = Amethyst::ModInfo;

    std::unique_ptr<Amethyst::RuntimeImporter> mRuntimeImporter;
    ModuleHandle mHandle;

    // Metadata and stuff
    Amethyst::ModInfo mInfo;

    Mod() = delete;
    Mod(const std::string& modName);
    Mod(const std::string& modName, HMODULE moduleHandle);
    Mod(const Mod&) = delete;
    Mod& operator=(const Mod&) = delete;
    Mod(Mod&& other) noexcept;
    Mod& operator=(Mod&&) noexcept = delete;
    ~Mod();

    const ModuleHandle& GetHandle() const;
    Amethyst::RuntimeImporter& GetRuntimeImporter() const;

    template <typename T = FARPROC>
    T GetFunction(const char* functionName) const
    {
        return reinterpret_cast<T>(GetProcAddress(mHandle, functionName));
    }

    bool operator==(const Mod& other) const;
    static Mod::Info GetInfo(const std::string& modName);
    static fs::path GetTemporaryLibrary(const std::string& modName);
};
} // namespace Amethyst