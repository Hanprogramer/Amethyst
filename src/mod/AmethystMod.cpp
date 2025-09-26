#include "mod/AmethystMod.hpp"

#include "amethyst/runtime/ModContext.hpp"

#include "hooks/ui/UIHooks.hpp"
#include "hooks/item/ItemHooks.hpp"
#include "hooks/RenderingHooks.hpp"
#include "hooks/Hooks.hpp"
#include "hooks/InputHooks.hpp"
#include "hooks/ResourceHooks.hpp"
#include "hooks/NetworkingHooks.hpp"

ModFunction void Initialize(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Amethyst::InitializeAmethystMod(ctx, mod);
    Log::Info("Initializing runtime mod: '{}'", mod.mInfo->GetVersionedName());
    SemVersion version = ctx.mPackageInfo.mVersion;

    if (version.mMajor != MOD_TARGET_VERSION_MAJOR || version.mMinor != MOD_TARGET_VERSION_MINOR || version.mPatch != MOD_TARGET_VERSION_PATCH) {
        Log::Warning("{} has been made for Minecraft version {}.{}.{}, detected version {}.{}.{}\n\t> It should be expected that things may break on this version.\n\t> We will not provide support for unintended versions.",
                     mod.mInfo->GetVersionedName(),
                     MOD_TARGET_VERSION_MAJOR, MOD_TARGET_VERSION_MINOR, MOD_TARGET_VERSION_PATCH,
                     version.mMajor, version.mMinor, version.mPatch);
    }
    else {
        Log::Info("Minecraft Version: {}.{}.{}", version.mMajor, version.mMinor, version.mPatch);
    }

    CreateInputHooks();
    CreateResourceHooks();
    CreateStartScreenHooks();
    CreateModFunctionHooks();
    CreateNetworkingHooks();
    CreateUIHooks();
    CreateItemHooks();
    CreateRenderingHooks();
}

ModFunction void Shutdown(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Log::Info("Shutting down runtime mod: '{}'", mod.mInfo->GetVersionedName());
    Amethyst::ShutdownAmethystMod();
}