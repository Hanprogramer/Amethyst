#include "ItemRegistryHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/world/item/Item.hpp>
#include <mc/src/common/world/item/registry/CreativeItemRegistry.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/CraftingScreenController.hpp>
#include <algorithm>

SafetyHookInline _VanillaItems__addConstructionCategory;

void VanillaItems__addConstructionCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addConstructionCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);

    auto& sharedCtx = Amethyst::GetCurrentThreadCtx();
    auto& creativeReg = sharedCtx.mCreativeRegistry;

    creativeReg.GetVanillaCategory(CreativeItemCategory::Construction)._RegisterItems(ref);
    
}

void CreateItemRegistryHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, _addConstructionCategory);
}
