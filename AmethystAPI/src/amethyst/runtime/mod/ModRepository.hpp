#pragma once
#include <unordered_map>
#include <string>

#include "amethyst/runtime/mod/ModInfo.hpp"

namespace Amethyst {
using ModInfoMap = std::unordered_map<std::string, ModInfo>;
class ModRepository {
    ModInfoMap mMods;
    std::vector<ModError> mErrors;

public:
    ModRepository() = default;
    ~ModRepository() = default;

    ModRepository(const ModRepository&) = delete;
    ModRepository& operator=(const ModRepository&) = delete;
    ModRepository(ModRepository&&) = delete;
    ModRepository& operator=(ModRepository&&) = delete;

    void ScanDirectory(const fs::path& directory, bool skipRuntimes = true);
    void Clear();

    const ModInfoMap& GetMods() const;
    const std::vector<ModError>& GetErrors() const;

    const ModInfo* GetModByUUID(const std::string& uuid) const;
    const ModInfo* GetModByNamespace(const std::string& modNamespace) const;

    bool HasModUUID(const std::string& uuid) const;
    bool HasModNamespace(const std::string& modNamespace) const;
    bool HasErrors() const;

    size_t GetModCount() const;
};
} // namespace Amethyst