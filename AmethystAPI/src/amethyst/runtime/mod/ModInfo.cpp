
#include "Json.hpp"
#include "amethyst/Log.hpp"
#include <fstream>
#include "ModInfo.hpp"

namespace Amethyst {
ModInfo::ModInfo(
    const std::string& uuid,
    const std::string& modNamespace,
    const std::string& name,
    const std::string& loggingName,
    const std::string& friendlyName,
    const Amethyst::Version& version,
    const std::vector<std::string>& authors,
    const std::vector<ModDependency>& dependencies,
    const fs::path& directory,
    const std::string& libraryName) : 
    UUID(uuid),
    Namespace(modNamespace),
    Name(name),
    LoggingName(loggingName),
    FriendlyName(friendlyName),
    Version(version),
    Authors(authors),
    Dependencies(dependencies),
    Directory(directory),
    LibraryName(libraryName)
{
}

std::string ModInfo::GetVersionedName() const
{
    return std::format("{}@{}", Name, Version.to_string());
}

bool ModInfo::Equals(const ModInfo& other, bool compareVersions) const
{
    return UUID == other.UUID && Namespace == other.Namespace && (!compareVersions || Version == other.Version);
}

bool ModInfo::operator==(const ModInfo& other) const
{
    return Equals(other);
}

bool ModInfo::operator!=(const ModInfo& other) const
{
    return !(*this == other);
}

bool ModInfo::operator<(const ModInfo& other) const 
{
    return std::tie(Namespace, UUID) < std::tie(other.Namespace, other.UUID);
}

inline bool ModInfo::IsSameMod(const ModInfo& other) const
{
    return Equals(other, false);
}

ModInfo ModInfo::FromFile(const fs::path& jsonFile)
{
    std::ifstream modConfigFile(jsonFile);

    Assert(modConfigFile.is_open(), "Failed to open mod.json, at '{}'", jsonFile.generic_string());

    std::stringstream buffer;
    buffer << modConfigFile.rdbuf();
    modConfigFile.close();
    std::string fileContents = buffer.str();

    nlohmann::json j = nlohmann::json::parse(fileContents);
    Assert(j["meta"].is_object(), "Invalid mod info JSON: 'meta' is not an object");
    nlohmann::json meta = j["meta"];
    Assert(meta["uuid"].is_string(), "Invalid mod info JSON: 'meta.uuid' is not a string");
    Assert(meta["namespace"].is_string(), "Invalid mod info JSON: 'meta.namespace' is not a string");
    Assert(meta["name"].is_string(), "Invalid mod info JSON: 'meta.name' is not a string");
    Assert(meta["version"].is_string(), "Invalid mod info JSON: 'meta.version' is not a string");

    std::string uuid = meta["uuid"].get<std::string>();
    std::string modNamespace = meta["namespace"].get<std::string>();
    std::string name = meta["name"].get<std::string>();
    Amethyst::Version version;
    if (!semver::parse(meta["version"].get<std::string>(), version)) {
        Assert(false, "Invalid mod info JSON: 'meta.version' is not a valid semantic version");
    }

    std::string loggingName = name;
    std::string friendlyName = name;
    std::vector<std::string> authors;
    std::vector<ModDependency> dependencies;

    if (meta.contains("logname") && meta["logname"].is_string()) {
        loggingName = meta["logname"].get<std::string>();
    }

    if (meta.contains("friendlyname") && meta["friendlyname"].is_string()) {
        friendlyName = meta["friendlyname"].get<std::string>();
    }

    if (meta.contains("author")) {
        if (meta["author"].is_string()) {
            authors.push_back(meta["author"].get<std::string>());
        }
        else if (meta["author"].is_array()) {
            for (const auto& author : meta["author"]) {
                if (author.is_string()) {
                    authors.push_back(author.get<std::string>());
                }
            }
        }
    }

    if (meta.contains("dependencies") && meta["dependencies"].is_array()) {
        for (const auto& dependencyObj : meta["dependencies"]) {
            if (dependencyObj.is_object() && dependencyObj.contains("min_version")) {
                auto verStr = dependencyObj["min_version"].get<std::string>();
                Amethyst::Version depVer;
                if (!semver::parse(verStr, depVer))
                    continue;

                dependencies.push_back(ModDependency(
                    dependencyObj.value("uuid", ""),
                    dependencyObj.value("namespace", ""),
                    depVer,
                    dependencyObj.value("is_soft", false)
                ));
            }
        }
    }

    std::string versionedName = std::format("{}@{}", name, version.to_string());
    fs::path directory = jsonFile.parent_path();
    std::string libraryName = std::format("{}.dll", name);

    Assert(fs::exists(directory / libraryName), "Could not find '{}', for mod '{}'.", (directory / libraryName).generic_string(), versionedName);

    return ModInfo(uuid, modNamespace, name, loggingName, friendlyName, version, authors, dependencies, directory, libraryName);
}
} // namespace Amethyst