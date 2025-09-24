#pragma once
#include <string>
#include <vector>
#include <format>

namespace Amethyst {
class ModInfo {
public:
    const std::string UUID;
    const std::string Namespace;
    const std::string Name;
    const std::string LoggingName;
    const std::string FriendlyName;
    const std::string Version;
    const std::vector<std::string> Authors;

    ModInfo() = delete;
    ModInfo(
        const std::string& uuid,
        const std::string& modnamespace,
        const std::string& name,
        const std::string& loggingName,
        const std::string& friendlyName,
        const std::string& version,
        const std::vector<std::string>& authors
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
        return !Equals(other, true);
    }

    bool IsSameMod(const ModInfo& other) const {
        return Equals(other, false);
    }

    static ModInfo FromJson(const std::string& jsonString);
    std::string ToJson() const;
};
} // namespace Amethyst

namespace std {
    template<>
    struct hash<Amethyst::ModInfo> {
        size_t operator()(const Amethyst::ModInfo& modInfo) const {
            return (
                (hash<std::string>()(modInfo.UUID) << 0) ^ 
                (hash<std::string>()(modInfo.Namespace) << 1) ^ 
                (hash<std::string>()(modInfo.Version) << 2)
            );
        }
    };
} // namespace std