#include "ModInfo.hpp"
#include "Json.hpp"
#include "amethyst/Log.hpp"

namespace Amethyst {
ModInfo::ModInfo(
    const std::string& uuid,
    const std::string& modNamespace,
    const std::string& name,
    const std::string& loggingName,
    const std::string& friendlyName,
    const std::string& version,
    const std::vector<std::string>& authors) : 
    UUID(uuid),
    Namespace(modNamespace),
    Name(name),
    LoggingName(loggingName),
    FriendlyName(friendlyName),
    Version(version),
    Authors(authors)
{
}

ModInfo::ModInfo(const ModInfo& other) : 
    UUID(other.UUID),
    Namespace(other.Namespace),
    Name(other.Name),
    LoggingName(other.LoggingName),
    FriendlyName(other.FriendlyName),
    Version(other.Version),
    Authors(other.Authors)
{
}

ModInfo ModInfo::FromJson(const std::string& jsonString)
{
    nlohmann::json j = nlohmann::json::parse(jsonString);
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

    return ModInfo(uuid, modNamespace, name, loggingName, friendlyName, version, authors);
}

std::string ModInfo::ToJson() const
{
    nlohmann::json j;
    j["meta"] = {
        {"uuid", UUID},
        {"namespace", Namespace},
        {"name", Name},
        {"logname", LoggingName},
        {"friendlyname", FriendlyName},
        {"version", Version},
        {"author", Authors}
    };
    return j.dump(4);
}
} // namespace Amethyst