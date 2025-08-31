#pragma once
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include "amethyst/runtime/mod/Mod.hpp"

namespace Amethyst {
struct Pack {
    Mod::Metadata metadata;
    std::string path;
    PackType type;
};

class PackManager {
public:
    PackManager();
    ~PackManager();

    void RegisterNewPack(const Mod::Metadata& metadata, const std::string& path, PackType type);
    const std::unordered_map<std::string, std::unordered_map<std::string, Pack>>& GetPacks() const;

private:
    friend class AmethystContext;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Pack>> mPacks;
};

}