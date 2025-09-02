#include "hooks/ResourceHooks.hpp"
#include "minecraft/src-vanilla/vanilla_shared/common/resources/VanillaInPackagePacks.hpp"
#include "minecraft/src-vanilla/vanilla_client/common/module/VanillaGameModuleClient.hpp"
#include "minecraft/src-vanilla/vanilla_shared/common/server/module/VanillaGameModuleServer.hpp"
#include "minecraft/src/common/resources/ResourcePackRepository.hpp"

SafetyHookInline _VanillaGameModuleClient_initializeResourceStack;
SafetyHookInline _VanillaGameModuleServer_initializeBehaviorStack;
SafetyHookInline _ResourcePackRepository_initializePackSource;

void VanillaGameModuleClient_initializeResourceStack(VanillaGameModuleClient* self, const Experiments& experiments, const gsl::not_null<Bedrock::NonOwnerPointer<ResourcePackRepository>>& repository, ResourcePackStack& stack, const BaseGameVersion& baseGameVer, GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    auto& context = *AmethystRuntime::getContext();
    context.mPackManager->AddResourcePacksToStack(repository, stack);
    _VanillaGameModuleClient_initializeResourceStack.thiscall<void, VanillaGameModuleClient*, const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<ResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase>(self, experiments, repository, stack, baseGameVer, loadingPhase);
}

void VanillaGameModuleServer_initializeBehaviorStack(VanillaGameModuleServer* self, const Experiments& experiments, const gsl::not_null<Bedrock::NonOwnerPointer<ResourcePackRepository>>& repository, ResourcePackStack& stack, const BaseGameVersion& baseGameVer, GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    auto& context = *AmethystRuntime::getContext();
    context.mPackManager->AddBehaviorPacksToStack(repository, stack);
    _VanillaGameModuleServer_initializeBehaviorStack.thiscall<void, VanillaGameModuleServer*, const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<ResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase>(self, experiments, repository, stack, baseGameVer, loadingPhase);
}

void ResourcePackRepository_initializePackSource(ResourcePackRepository* self) 
{
    _ResourcePackRepository_initializePackSource.thiscall<void, ResourcePackRepository*>(self);
    Log::Info("[AmethystRuntime] Initializing mod resource and behavior pack sources...");
    auto& context = *AmethystRuntime::getContext();
    auto& packManager = *context.mPackManager;

    // Add mod "resource_packs" and "behavior_packs" to the CompositePackSource
    for (auto& [nameVer, packs] : packManager.GetPacks()) {
        fs::path modBasePath = GetAmethystFolder() / "mods" / nameVer;

        // Check if the mod has resource packs
        bool hasResourcePacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
            return pair.second.type == PackType::Resources;
        }) != packs.end();

        // Check if the mod has behavior packs
        bool hasBehaviorPacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
            return pair.second.type == PackType::Behavior;
        }) != packs.end();

        // Add the resource pack source if it has resource packs
        if (hasResourcePacks) {
            auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "resource_packs").string()), PackType::Resources, PackOrigin::User, false);
            self->mPackSource->mPackSources.push_back(&packSource);
        }

        // Add the behavior pack source if it has behavior packs
        if (hasBehaviorPacks) {
            auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "behavior_packs").string()), PackType::Behavior, PackOrigin::User, false);
            self->mPackSource->mPackSources.push_back(&packSource);
        }
    }
}

void CreateResourceHooks() {
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();

    hooks.RegisterFunction<&VanillaGameModuleClient::initializeResourceStack>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9 4C 89 8D");
    hooks.CreateHook<&VanillaGameModuleClient::initializeResourceStack>(_VanillaGameModuleClient_initializeResourceStack, &VanillaGameModuleClient_initializeResourceStack);

    hooks.RegisterFunction<&VanillaGameModuleServer::initializeBehaviorStack>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F9 4D 8B F0 4C 8B BD");
    hooks.CreateHook<&VanillaGameModuleServer::initializeBehaviorStack>(_VanillaGameModuleServer_initializeBehaviorStack, &VanillaGameModuleServer_initializeBehaviorStack);

    hooks.RegisterFunction<&ResourcePackRepository::_initializePackSource>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F1 45 33 E4 0F 57 C9 F3 0F 7F 4D ? 41 8B FC");
    hooks.CreateHook<&ResourcePackRepository::_initializePackSource>(_ResourcePackRepository_initializePackSource, &ResourcePackRepository_initializePackSource);
}