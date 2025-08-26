#include "SymbolLoader.hpp"
#include "Json.hpp"
#include "amethyst/Utility.hpp"

void Amethyst::SymbolLoader::Start(const Config& config) 
{
    // Load the runtime's symbols (required to have them)
    fs::path runtimeSymbolsPath = GetAmethystFolder() / "mods" / config.injectedMod / "symbols.json";
    std::string runtimeSymbols = ReadTextFile(runtimeSymbolsPath);

    // Load symbols provided by the runtime
    if (fs::exists(runtimeSymbolsPath)) LoadDefinitions(runtimeSymbols);

    // Load definitions provided by mods
    for (const auto& mod : config.mods) {
        fs::path modSymbolsPath = GetAmethystFolder() / "mods" / mod / "symbols.json";
        if (!fs::exists(modSymbolsPath)) continue;
        
        std::string modSymbols = ReadTextFile(modSymbolsPath);
        LoadDefinitions(modSymbols);
    }

    Log::Info("[SymbolLoader] Loaded {} symbols!", (uint64_t)this->mSymbolHashToAddress.size());
}

void Amethyst::SymbolLoader::LoadDefinitions(const std::string& unparsedJson)
{
    auto parsed = nlohmann::json::parse(unparsedJson);
    if (!parsed.is_object()) 
    {
        Log::Warning("[SymbolLoader] Definitions file is not a valid JSON object.");
        return;
    }
    
    for (const auto& [key, value] : parsed.items()) {
        HashedString hashedKey(key);

        if (!value.is_string()) {
            Log::Warning("[SymbolLoader] Value of key '{}' expected to be of type string. Skipping.", key);
            continue;
        }

        this->mSymbolHashToAddress[hashedKey.getHash()] = SigScan(value.get<std::string>());
    }
}