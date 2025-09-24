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
    ModuleHandle mHandle;
    std::shared_ptr<Amethyst::RuntimeImporter> mRuntimeImporter;
    bool mIsLoaded = false;

public:
    using Info = Amethyst::ModInfo;

    // Metadata and stuff
    Amethyst::ModInfo mInfo;

    Mod() = delete;
    Mod(const Mod&) = delete;
    Mod& operator=(const Mod&) = delete;
    Mod& operator=(Mod&&) noexcept = delete;

    explicit Mod(const Mod::Info& info);
    Mod(Mod&& other) noexcept;
    ~Mod();

    void Load();
    void Unload();
    void Attach(HMODULE moduleHandle);

    const ModuleHandle& GetHandle() const;
    Amethyst::RuntimeImporter& GetRuntimeImporter() const;

    template <typename T = FARPROC>
    T GetFunction(const char* functionName) const
    {
        return reinterpret_cast<T>(GetProcAddress(mHandle, functionName));
    }

    bool IsLoaded() const;

    bool operator==(const Mod& other) const;
    static Mod::Info GetInfo(const std::string& modName);
    static fs::path GetTemporaryLibrary(const std::string& modName);
};
} // namespace Amethyst