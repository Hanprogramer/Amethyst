#include "amethyst/Config.hpp"

Config::Config(std::string& text)
{
    // Parse config.json into json
    json data;

    try {
        data = json::parse(text);
    }
    catch (std::exception e) {
        Assert(false, "Failed to parse config file 'launcher_config.json'");
    }

    // Verify all fields are correct in config.json

    Assert(data["runtime"].is_string(), "Required field \"runtime\" should be of type \"string\" in config.json");
    Assert(data["mods"].is_array(), "Required field \"mods\" should be of type \"string[]\" in config.json");
    Assert(data["developer_mode"].is_boolean(), "Required field \"developer_mode\" should be of type \"boolean\" in config.json");


    for (const auto& element : data["mods"]) {
        Assert(element.is_string(), "Array \"mods\" in config.json should only contain strings");
    }

    // Set values
    this->injectedMod = data["runtime"];
    this->mods = data["mods"];
    this->promptDebugger = data["developer_mode"];
}