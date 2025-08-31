#include "amethyst/runtime/resource/PackManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include <winrt/Windows.Storage.h>
#include <fstream>

Amethyst::PackManager::PackManager(AmethystContext* amethyst) : 
    mAmethyst(amethyst)
{}

Amethyst::PackManager::~PackManager() {}

void Amethyst::PackManager::RegisterNewPack(const Mod::Metadata& metadata, const std::string& path, PackType type)
{
	std::string key = metadata.GetVersionedName();

	// Check if the mod is on the list of packs, if not add it
	if (!mPacks.contains(key)) {
        mPacks[key] = {};
	}

	// Check if the pack path is already registered for this mod
    if (mPacks[key].contains(path)) {
		Log::Warning("[PackManager] Pack '{}' of type {} for '{}' is already registered, skipping.", path, static_cast<int>(type), key);
		return;
    }

    auto fullPath = GetAmethystFolder() / "mods" / path;
    auto manifestPath = fullPath / "manifest.json";

    // Check if the pack contains a manifest.json
    if (!fs::exists(manifestPath)) {
        Log::Warning("[PackManager] Pack '{}' for '{}' does not contain a manifest.json, skipping.", path, key);
        return;
    }

    // Try to read the manifest.json to ensure it's valid
    std::ifstream manifestFile(manifestPath, std::ios::binary);
    Assert(manifestFile.is_open(), "[PackManager] Failed to open manifest.json for pack '{}' of '{}'", path, key);
    std::string manifestContents((std::istreambuf_iterator<char>(manifestFile)), std::istreambuf_iterator<char>());

    // Try to parse the manifest.json
    auto manifestJson = json::parse(manifestContents);
    if (!manifestJson.is_object()) {
        Log::Warning("[PackManager] manifest.json for pack '{}' of '{}' is not a valid json object, skipping.", path, key);
        return;
    }

    // Ensure it has a header object
    auto& header = manifestJson["header"];
    if (!header.is_object()) {
        Log::Warning("[PackManager] manifest.json for pack '{}' of '{}' does not contain a valid \"header\" object, skipping.", path, key);
        return;
    }

    // Ensure it has a uuid string in the header
    auto& uuid = header["uuid"];
    if (!uuid.is_string()) {
        Log::Warning("[PackManager] manifest.json for pack '{}' of '{}' does not contain a valid \"uuid\" string in the \"header\" object, skipping.", path, key);
        return;
    }
    
    // Ensure it has a version array in the header
    auto& version = header["version"];
    if (!version.is_array() || version.size() != 3 || !version[0].is_number_unsigned() || !version[1].is_number_unsigned() || !version[2].is_number_unsigned()) {
        Log::Warning("[PackManager] manifest.json for pack '{}' of '{}' does not contain a valid \"version\" array in the \"header\" object, skipping.", path, key);
        return;
    }

    mce::UUID packUuid = mce::UUID::fromString(uuid.get<std::string>());
    SemVersion semVersion = {version[0].get<uint16_t>(), version[1].get<uint16_t>(), version[2].get<uint16_t>()};

	// Insert the new pack
    mPacks[key].insert({path, Pack{metadata, path, packUuid, semVersion, type}});
	Log::Info("[PackManager] Registered pack '{}'.", path);
}

const std::unordered_map<std::string, std::unordered_map<std::string, Amethyst::Pack>>& Amethyst::PackManager::GetPacks() const
{
	return mPacks;
}

const fs::path& Amethyst::PackManager::GetModsFolderRelativeToPackage()
{
    // Relative path from the game install directory to the local app data for the package
    // Tried to use fs::relative but it didn't work so for now it's okay to hardcode this
    static auto localForPackage =
        fs::path("../../../../../") /
        "Local" /
        "Packages" /
        mAmethyst->mPackageInfo.mFamilyName /
        "LocalState" /
        "games" /
        "com.mojang" /
        "amethyst" /
        "mods";

    return localForPackage;
}
