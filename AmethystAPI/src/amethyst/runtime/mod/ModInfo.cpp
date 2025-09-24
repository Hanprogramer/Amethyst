#include "ModInfo.hpp"
#include "Json.hpp"
#include "amethyst/Log.hpp"
#include <fstream>

namespace Amethyst {
ModInfo::ModInfo(
    const std::string& uuid,
    const std::string& modNamespace,
    const std::string& name,
    const std::string& loggingName,
    const std::string& friendlyName,
    const std::string& version,
    const std::vector<std::string>& authors,
    const fs::path& directory,
    const std::string& libraryName) : 
    UUID(uuid),
    Namespace(modNamespace),
    Name(name),
    LoggingName(loggingName),
    FriendlyName(friendlyName),
    Version(version),
    Authors(authors),
    Directory(directory),
    LibraryName(libraryName)
{
}

ModInfo::ModInfo(const ModInfo& other) : 
    UUID(other.UUID),
    Namespace(other.Namespace),
    Name(other.Name),
    LoggingName(other.LoggingName),
    FriendlyName(other.FriendlyName),
    Version(other.Version),
    Authors(other.Authors),
    Directory(other.Directory),
    LibraryName(other.LibraryName)
{
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
    std::string version = meta["version"].get<std::string>();
    std::string loggingName = name;
    std::string friendlyName = name;
    std::vector<std::string> authors;

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

    std::string versionedName = std::format("{}@{}", name, version);
    fs::path directory = jsonFile.parent_path();
    std::string libraryName = std::format("{}.dll", versionedName);

    Assert(fs::exists(directory / libraryName), "Could not find '{}', for mod '{}'.", (directory / libraryName).generic_string(), versionedName);

    return ModInfo(uuid, modNamespace, name, loggingName, friendlyName, version, authors, directory, libraryName);
}
} // namespace Amethyst