#include "hooks/ResourceHooks.hpp"
#include "minecraft/src-vanilla/vanilla_shared/common/resources/VanillaInPackagePacks.hpp"
#include "minecraft/src-vanilla/vanilla_client/common/module/VanillaGameModuleClient.hpp"
#include "minecraft/src-vanilla/vanilla_shared/common/server/module/VanillaGameModuleServer.hpp"

SafetyHookInline _VanillaInPackagePacks_getPacks;
SafetyHookInline _VanillaGameModuleClient_initializeResourceStack;
SafetyHookInline _VanillaGameModuleServer_initializeBehaviorStack;

void VanillaInPackagePacks_getPacks(VanillaInPackagePacks* self, std::vector<IInPackagePacks::MetaData>& result, PackType packType)
{
    _VanillaInPackagePacks_getPacks.thiscall<void, VanillaInPackagePacks*, std::vector<IInPackagePacks::MetaData>&, PackType>(self, result, packType);
    
    auto& context = *AmethystRuntime::getContext();

    // Relative path from the game install directory to the local app data for the package
    // Tried to use fs::relative but it didn't work so for now it's okay to hardcode this
    static auto localForPackage = 
        fs::path("../../../../../") / 
        "Local" /
        "Packages" /
        context.mPackageInfo.mFamilyName / 
        "LocalState" /
        "games" /
        "com.mojang" /
        "amethyst" /
        "mods";

    // Iterate over all registered packs
    for (auto& [nameVer, packs] : context.mPackManager->GetPacks()) {
        for (auto& [path, pack] : packs) {
            if (pack.type == packType) {
                // Add the pack to the list
                result.emplace_back(Core::Path((localForPackage / path).string()), false, PackCategory::Standard);
            }
        }
    }
}

void VanillaGameModuleClient_initializeResourceStack(VanillaGameModuleClient* self, const Experiments& experiments, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository, ResourcePackStack& stack, const BaseGameVersion& baseGameVer, GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    // TODO: Add resource packs to stack
    _VanillaGameModuleClient_initializeResourceStack.thiscall<void, VanillaGameModuleClient*, const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase>(self, experiments, repository, stack, baseGameVer, loadingPhase);
}

void VanillaGameModuleServer_initializeBehaviorStack(VanillaGameModuleServer* self, const Experiments& experiments, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository, ResourcePackStack& stack, const BaseGameVersion& baseGameVer, GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    // TODO: Add behavior packs to stack
    _VanillaGameModuleServer_initializeBehaviorStack.thiscall<void, VanillaGameModuleServer*, const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase>(self, experiments, repository, stack, baseGameVer, loadingPhase);
}

void CreateResourceHooks() {
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();

    hooks.RegisterFunction<&VanillaInPackagePacks::getPacks>("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 55 ? 33 F6");
    hooks.CreateHook<&VanillaInPackagePacks::getPacks>(_VanillaInPackagePacks_getPacks, &VanillaInPackagePacks_getPacks);

    hooks.RegisterFunction<&VanillaGameModuleClient::initializeResourceStack>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9 4C 89 8D");
    hooks.CreateHook<&VanillaGameModuleClient::initializeResourceStack>(_VanillaGameModuleClient_initializeResourceStack, &VanillaGameModuleClient_initializeResourceStack);

    hooks.RegisterFunction<&VanillaGameModuleServer::initializeBehaviorStack>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F9 4D 8B F0 4C 8B BD");
    hooks.CreateHook<&VanillaGameModuleServer::initializeBehaviorStack>(_VanillaGameModuleServer_initializeBehaviorStack, &VanillaGameModuleServer_initializeBehaviorStack);
}