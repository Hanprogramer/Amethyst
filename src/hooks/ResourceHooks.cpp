#include "hooks/ResourceHooks.hpp"
#include "mc/src-vanilla/vanilla_shared/common/resources/VanillaInPackagePacks.hpp"
#include "mc/src-vanilla/vanilla_client/common/module/VanillaGameModuleClient.hpp"
#include "mc/src-vanilla/vanilla_shared/common/server/module/VanillaGameModuleServer.hpp"
#include "mc/src/common/resources/ResourcePackRepository.hpp"
#include "amethyst/runtime/ModContext.hpp"

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
    Log::Info("Initializing mod resource and behavior pack sources...");
    auto& context = *AmethystRuntime::getContext();
    auto& packManager = *context.mPackManager;

    // Add mod "resource_packs" and "behavior_packs" to the CompositePackSource
    for (auto& [nameVer, packs] : packManager.GetPacks()) {
        auto& platform = Amethyst::GetPlatform();
        fs::path modBasePath = platform.GetAmethystFolder() / "mods" / nameVer;

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

    hooks.CreateVirtualHook<&VanillaGameModuleClient::initializeResourceStack>(
        VanillaGameModuleClient::$vtable_for_this,
        _VanillaGameModuleClient_initializeResourceStack,
        VanillaGameModuleClient_initializeResourceStack
    );

    hooks.CreateVirtualHook<&VanillaGameModuleServer::initializeBehaviorStack>(
        VanillaGameModuleServer::$vtable_for_this,
        _VanillaGameModuleServer_initializeBehaviorStack,
        VanillaGameModuleServer_initializeBehaviorStack
    );

    hooks.CreateDirectHook<&ResourcePackRepository::_initializePackSource>(_ResourcePackRepository_initializePackSource, &ResourcePackRepository_initializePackSource);
}