#pragma once
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-deps/core/resource/ResourceHelper.hpp"
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/Memory.hpp"

class AmethystContext;
class ResourcePackStack;
class ResourcePackRepository;

namespace Amethyst {
enum class PackPriority {
    Lowest = 0,
    Lower = 1,
    Low = 2,
    Normal = 3,
    High = 4,
    Higher = 5,
    ExtremelyHigh = 6
};

struct Pack {
    Mod::Metadata metadata;
    std::string path;
    mce::UUID uuid;
    SemVersion version;
    PackType type;
    PackPriority priority;
};

class PackManager {
public:
    PackManager(AmethystContext* amethyst);
    PackManager(const PackManager&) = delete;
    PackManager(PackManager&&) = delete;
    PackManager& operator=(const PackManager&) = delete;
    PackManager& operator=(PackManager&&) = delete;
    ~PackManager();

    void RegisterNewPack(const Mod::Metadata& metadata, const std::string& path, PackType type, PackPriority priority = PackPriority::Normal);
    const std::unordered_map<std::string, std::unordered_map<std::string, Pack>>& GetPacks() const;
    void AddResourcePacksToStack(const Bedrock::NonOwnerPointer<ResourcePackRepository>& repository, ResourcePackStack& stack);
    void AddBehaviorPacksToStack(const Bedrock::NonOwnerPointer<ResourcePackRepository>& repository, ResourcePackStack& stack);

private:
    AmethystContext* mAmethyst;
    friend class AmethystContext;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Pack>> mPacks;
};
}