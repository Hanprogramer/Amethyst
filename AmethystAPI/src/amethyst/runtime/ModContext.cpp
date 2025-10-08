#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/Minecraft.hpp>

AmethystContext* _AmethystContextInstance;
const Amethyst::Mod* _OwnMod;

void Amethyst::InitializeAmethystMod(AmethystContext& context, const Mod& mod)
{
    // Check if the mod has a resource pack and register it if it does
    if (fs::exists(mod.mInfo->Directory / "resource_packs" / "main_rp" / "manifest.json"))
        context.mPackManager->RegisterNewPack(&mod, "main_rp", PackType::Resources);

    // Check if the mod has a behavior pack and register it if it does
    if (fs::exists(mod.mInfo->Directory / "behavior_packs" / "main_bp" / "manifest.json"))
        context.mPackManager->RegisterNewPack(&mod, "main_bp", PackType::Behavior);

    // Store a persistent AmethystContext instance
    _AmethystContextInstance = &context;

    // Store our own mod info for later retrieval
    _OwnMod = &mod;
}

AmethystContext& Amethyst::GetContext()
{
    return *_AmethystContextInstance;
}

Amethyst::EventBus& Amethyst::GetEventBus()
{
    return *_AmethystContextInstance->mEventBus.get();
}

Amethyst::HookManager& Amethyst::GetHookManager()
{
    return *_AmethystContextInstance->mHookManager.get();
}

Amethyst::PatchManager& Amethyst::GetPatchManager()
{
    return *_AmethystContextInstance->mPatchManager.get();
}

Amethyst::EnumAllocator& Amethyst::GetEnumAllocator()
{
    return *_AmethystContextInstance->mEnumAllocator.get();
}

Amethyst::NetworkManager& Amethyst::GetNetworkManager()
{
    return *_AmethystContextInstance->mNetworkManager.get();
}

Amethyst::Platform& Amethyst::GetPlatform()
{
    Amethyst::Platform* platform = _AmethystContextInstance->mPlatform.get();

    if (platform == nullptr) {
        AssertFail("Amethyst::GetPlatform was nullptr!");
    }

    return *platform;
}

Minecraft* Amethyst::GetMinecraft()
{
    return _AmethystContextInstance->mClientInstance->mMinecraft;
}

Level* Amethyst::GetLevel()
{
    ClientInstance* ci = _AmethystContextInstance->mClientInstance;
    if (!ci) return nullptr;
    return ci->mMinecraft->getLevel();
}

ClientInstance* Amethyst::GetClientInstance()
{
    return _AmethystContextInstance->mClientInstance;
}

const Amethyst::Mod* Amethyst::GetOwnMod()
{
    return _OwnMod;
}
