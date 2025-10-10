#include "ItemRegistryHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/world/item/Item.hpp>
#include <mc/src/common/world/item/registry/CreativeItemRegistry.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/CraftingScreenController.hpp>
#include <algorithm>

SafetyHookInline _VanillaItems__addItemsCategory;
SafetyHookInline _VanillaItems__addCommandOnlyCategory;
SafetyHookInline _VanillaItems__addEquipmentCategory;
SafetyHookInline _VanillaItems__addNatureCategory;
SafetyHookInline _VanillaItems__addConstructionCategory;

void RegisterCreativeItems(ItemRegistryRef ref, CreativeItemCategory category) {
    auto& sharedCtx = Amethyst::GetCurrentThreadCtx();
    auto& vanillaCategory = sharedCtx.mCreativeRegistry.GetVanillaCategory(CreativeItemCategory::Construction);
    vanillaCategory._RegisterItems(ref);
}

void VanillaItems__addItemsCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addItemsCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Items);
}

void VanillaItems__addCommandOnlyCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addCommandOnlyCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::ItemCommandOnly);
}

void VanillaItems__addEquipmentCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addEquipmentCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Equipment);
}

void VanillaItems__addNatureCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addNatureCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Nature);
}

void VanillaItems__addConstructionCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addConstructionCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Construction);
}

void CreateItemRegistryHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, _addItemsCategory);
    HOOK(VanillaItems, _addCommandOnlyCategory);
    HOOK(VanillaItems, _addEquipmentCategory);
    HOOK(VanillaItems, _addNatureCategory);
    HOOK(VanillaItems, _addConstructionCategory);
}
