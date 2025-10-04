#include "ItemRegistryHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/world/item/Item.hpp>
#include <mc/src/common/world/item/registry/CreativeItemRegistry.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/CraftingScreenController.hpp>
#include <algorithm>

SafetyHookInline _VanillaItems_serverInitCreativeItemsCallback;

void VanillaItems_serverInitCreativeItemsCallback(
    ItemRegistryRef ref, 
    ActorInfoRegistry* actorInfo, 
    BlockDefinitionGroup* blockDefs,
    CreativeItemRegistry* creativeReg, 
    bool something,
    const BaseGameVersion& version, 
    const Experiments& experiments
) {
    Log::Info("VanillaItems_serverInitCreativeItemsCallback! {}", creativeReg->mCreativeGroupCategories.size());

    _VanillaItems_serverInitCreativeItemsCallback.call<void, ItemRegistryRef, ActorInfoRegistry*, BlockDefinitionGroup*, CreativeItemRegistry*, bool, const BaseGameVersion&, const Experiments&>(ref, actorInfo, blockDefs, creativeReg, something, version, experiments);
}

SafetyHookInline _VanillaItems__addConstructionCategory;

void VanillaItems__addConstructionCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addConstructionCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);

    Log::Info("tabs size {}", CraftingScreenController::mCategoryTabs.size());

    for (auto& tab : CraftingScreenController::mCategoryTabs) {
        Log::Info(" - {} {}, category: {}, padding4: {}, padding8: {}", tab.mTabName, tab.mTabFactoryName, (uint32_t)tab.mCategory, tab.padding4, tab.padding8);
    }

    CraftingScreenController::CategoryTabInfo testTab;
    testTab.mCategory = (CreativeItemCategory)8;
    testTab.mTabName = "test_tab";
    testTab.mTabFactoryName = "test_tab_factory";
    testTab.padding4 = 0;
    testTab.padding8 = 0;

    // add a field once, if its not found
    auto it = std::find_if(CraftingScreenController::mCategoryTabs.begin(),
                           CraftingScreenController::mCategoryTabs.end(),
                           [](const CraftingScreenController::CategoryTabInfo& tab) {
                               return tab.mTabName == "test_tab";
                           });

    // Insert only if not found
    if (it == CraftingScreenController::mCategoryTabs.end()) {
        CraftingScreenController::mCategoryTabs.push_back(std::move(testTab));
    }

    Log::Info("VanillaItems::addConstructionCategory! {}", (uintptr_t)Item::mActiveCreativeItemCategory);
    Item::mActiveCreativeItemCategory = creative->newCreativeCategory("Test", (CreativeItemCategory)8);
    Item::mActiveCreativeGroupInfo = nullptr;

    const Block* testBlock = BlockTypeRegistry::getDefaultBlockState("fx_tests:test_block");
    Item::addCreativeItem(ref, *testBlock);
}

void CreateItemRegistryHooks()
{
    // temporarily disable
    return;


    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, serverInitCreativeItemsCallback);
    HOOK(VanillaItems, _addConstructionCategory);
}
