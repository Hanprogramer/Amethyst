#pragma once
#include "amethyst/runtime/mod/ModInfo.hpp"
#include <filesystem>
#include <unordered_map>
#include <string>

namespace fs = std::filesystem;
namespace Amethyst {
class ModRegistry {
    fs::path mModsDirectory;
    std::unordered_map<std::string, ModInfo> mRegisteredMods; // Keyed by UUID

    explicit ModRegistry(const fs::path& modsDirectory);
    void ScanForMods();

public:
    ModRegistry() = delete;
    ModRegistry(const ModRegistry&) = delete;
    ModRegistry& operator=(const ModRegistry&) = delete;
    ModRegistry& operator=(ModRegistry&&) noexcept = delete;
    ModRegistry(ModRegistry&&) noexcept = delete;

    const fs::path& GetModsDirectory() const;
    const std::unordered_map<std::string, ModInfo>& GetRegisteredMods() const;
    const ModInfo* GetModByUUID(const std::string& uuid) const;

};
} // namespace Amethyst