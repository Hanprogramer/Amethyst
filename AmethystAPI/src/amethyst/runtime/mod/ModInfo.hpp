#pragma once
#include <string>
#include <vector>
#include <format>

namespace Amethyst {
class ModDependency {
public:

};

class ModInfo {
public:
    const std::string UUID;
    const std::string Namespace;
    const std::string Name;
    const std::string LoggingName;
    const std::string FriendlyName;
    const std::string Version;
    const std::vector<std::string> Authors;
    const fs::path Directory;
    const std::string LibraryName;

    ModInfo() = delete;
    ModInfo(
        const std::string& uuid,
        const std::string& modnamespace,
        const std::string& name,
        const std::string& loggingName,
        const std::string& friendlyName,
        const std::string& version,
        const std::vector<std::string>& authors,
        const fs::path& directory,
        const std::string& libraryName
    );

    ModInfo(const ModInfo& other);
    ModInfo& operator=(const ModInfo& other) = delete;
    ModInfo(ModInfo&& other) noexcept = delete;
    ModInfo& operator=(ModInfo&& other) noexcept = delete;

    std::string GetVersionedName() const {
        return std::format("{}@{}", Name, Version);
    }

    bool Equals(const ModInfo& other, bool compareVersions = true) const {
        return UUID == other.UUID && Namespace == other.Namespace && (!compareVersions || Version == other.Version);
    }

    bool operator==(const ModInfo& other) const {
        return Equals(other, true);
    }

    bool operator!=(const ModInfo& other) const {
        return !(*this == other);
    }

    bool operator<(const ModInfo& other) const {
        return std::tie(Namespace, UUID, Version) < std::tie(other.Namespace, other.UUID, other.Version);
    }

    bool IsSameMod(const ModInfo& other) const {
        return Equals(other, false);
    }

    static ModInfo FromFile(const fs::path& jsonFile);
};
} // namespace Amethyst

namespace std {
    template<>
    struct hash<Amethyst::ModInfo> {
        size_t operator()(const Amethyst::ModInfo& modInfo) const {
            size_t h = hash<std::string>{}(modInfo.UUID);
            h ^= hash<std::string>{}(modInfo.Namespace) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= hash<std::string>{}(modInfo.Version) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
} // namespace std