#include "mod/AmethystMod.hpp"

#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"

#include "hooks/ui/UIHooks.hpp"
#include "hooks/item/ItemHooks.hpp"
#include "hooks/RenderingHooks.hpp"
#include "hooks/Hooks.hpp"
#include "hooks/InputHooks.hpp"
#include "hooks/ResourceHooks.hpp"
#include "hooks/NetworkingHooks.hpp"

extern AmethystContext* _AmethystContextInstance;
extern const Amethyst::Mod* _OwnMod;

ModFunction void Initialize(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Amethyst::InitializeAmethystMod(ctx, mod);

    Amethyst::EventBus& events = *ctx.mEventBus;
    events.AddListener<BeforeModShutdownEvent>([&](const BeforeModShutdownEvent& e) {
        Log::Info("Shutting down runtime mod: '{}'", mod.mInfo->GetVersionedName());
        _AmethystContextInstance = nullptr;
        _OwnMod = nullptr;
    });

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