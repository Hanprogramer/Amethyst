#include "amethyst/runtime/resource/PackManager.hpp"

Amethyst::PackManager::PackManager() {}
Amethyst::PackManager::~PackManager() {}

void Amethyst::PackManager::RegisterNewPack(const Mod::Metadata& metadata, const std::string& path, PackType type)
{
	std::string key = metadata.GetNameVersion();

	// Check if the mod is on the list of packs, if not add it
	if (!mPacks.contains(key)) {
        mPacks[key] = {};
	}

	// Check if the pack path is already registered for this mod
    if (mPacks[key].contains(path)) {
		Log::Warning("[PackManager] Pack '{}' of type {} for '{}' is already registered, skipping.", path, static_cast<int>(type), key);
		return;
    }

	// Insert the new pack
    mPacks[key].insert({path, Pack{metadata, path, type}});
	Log::Info("[PackManager] Registered pack '{}'.", path);
}

const std::unordered_map<std::string, std::unordered_map<std::string, Amethyst::Pack>>& Amethyst::PackManager::GetPacks() const
{
	return mPacks;
}