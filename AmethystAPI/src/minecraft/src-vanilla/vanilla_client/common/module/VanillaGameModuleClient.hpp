#pragma once
#include "minecraft/src-client/common/module/GameModuleClient.hpp"

class Experiments;
class IResourcePackRepository;
class ResourcePackStack;
class BaseGameVersion;

/* 1.21.0.3 - vftable: 0x4EBD550 */
class VanillaGameModuleClient {
public:
    // 1.21.0.3 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9 4C 89 8D
    void initializeResourceStack(const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};