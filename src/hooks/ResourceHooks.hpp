#pragma once
#include <string>

#include "loader/AmethystRuntime.hpp"
#include "amethyst/Memory.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/utility/InlineHook.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-vanilla/vanilla_shared/common/resources/VanillaInPackagePacks.hpp"
#include "mc/src-vanilla/vanilla_client/common/module/VanillaGameModuleClient.hpp"
#include "mc/src-vanilla/vanilla_shared/common/server/module/VanillaGameModuleServer.hpp"
#include "mc/src/common/resources/ResourcePackRepository.hpp"

class PackIdVersion;

namespace Amethyst::ResourceHooks {
inline Amethyst::InlineHook<decltype(&VanillaGameModuleClient::initializeResourceStack)> _initializeResourceStack;
inline Amethyst::InlineHook<decltype(&VanillaGameModuleServer::initializeBehaviorStack)> _initializeBehaviorStack;
inline Amethyst::InlineHook<decltype(&ResourcePackRepository::_initializePackSource)> __initializePackSource;

void initializeResourceStack(
    VanillaGameModuleClient* self,
    const Experiments& experiments,
    const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
    ResourcePackStack& stack,
    const BaseGameVersion& baseGameVer,
    GameModuleClient::ResourceLoadingPhase loadingPhase
);
void initializeBehaviorStack(
    VanillaGameModuleServer* self,
    const Experiments& experiments,
    const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
    ResourcePackStack& stack,
    const BaseGameVersion& baseGameVer,
    GameModuleClient::ResourceLoadingPhase loadingPhase
);
void initializePackSource(ResourcePackRepository* self);
void Create();
}

