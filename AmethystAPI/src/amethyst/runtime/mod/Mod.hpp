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

class AmethystContext;
namespace Amethyst {
class Mod {
    using InitializeFunction = void(*)(AmethystContext&, const Mod&);

    ModuleHandle mHandle;
    std::shared_ptr<Amethyst::RuntimeImporter> mRuntimeImporter;
    bool mIsLoaded = false;
    bool mIsInitialized = false;

    InitializeFunction mInitializeFunction = nullptr;

public:
    // Metadata and stuff
    std::shared_ptr<const ModInfo> mInfo;

    Mod() = delete;
    Mod(const Mod&) = delete;
    Mod& operator=(const Mod&) = delete;
    Mod& operator=(Mod&&) noexcept = delete;

    explicit Mod(const std::shared_ptr<const ModInfo>& info);
    Mod(Mod&& other) noexcept;
    ~Mod();

    std::optional<ModError> Load();
    void Unload();
    void Attach(HMODULE moduleHandle);

    const ModuleHandle& GetHandle() const;
    Amethyst::RuntimeImporter& GetRuntimeImporter() const;

    template <typename T = FARPROC>
    T GetFunction(const char* functionName) const
    {
        return reinterpret_cast<T>(GetProcAddress(mHandle, functionName));
    }

    InitializeFunction GetInitializeFunction();
    std::optional<ModError> CallInitialize(AmethystContext& ctx);

    bool IsLoaded() const;

    bool operator==(const Mod& other) const;
    static std::shared_ptr<const ModInfo> GetInfo(const std::string& modName);
    static fs::path GetTemporaryLibrary(const std::string& modName);
};
} // namespace Amethyst