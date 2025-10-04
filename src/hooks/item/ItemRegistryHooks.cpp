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

SafetyHookInline _CraftingScreenController__tabIndexToCollectionName;

std::string* CraftingScreenController__tabIndexToCollectionName(CraftingScreenController* self, std::string* res, InventoryLeftTabIndex tabIdx)
{
    _CraftingScreenController__tabIndexToCollectionName.call<std::string*, CraftingScreenController*, std::string*, InventoryLeftTabIndex>(self, res, tabIdx);

    if (tabIdx == (InventoryLeftTabIndex)8) {
        *res = "recipe_test";
    }

    //Log::Info("_tabIndexToCollectionName: {} for tabIdx {}", *res, (int64_t)tabIdx);

    return res;
}

SafetyHookInline _lambda_ScreenController_registerTabNameBinding;

void* lambda_ScreenController_registerTabNameBinding(void* a1, void* a2) {
    uint32_t* something = (uint32_t*)((uintptr_t)a1 + 4680);

    Log::Info("something: {}", *something); // seems to be some random thing each time for the test tab.

    // construction 2742786064

    std::string* res = _lambda_ScreenController_registerTabNameBinding.call<std::string*, void*, void*>(a1, a2);
    Log::Info("something res '{}'", *res);

    if (res->size() == 0) {
        *res = "craftingScreen.tab.test";
    }

    return (void*)res;
}

void CreateItemRegistryHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, serverInitCreativeItemsCallback);
    HOOK(VanillaItems, _addConstructionCategory);
    HOOK(CraftingScreenController, _tabIndexToCollectionName);

    hooks.CreateHookAbsolute(
        _lambda_ScreenController_registerTabNameBinding,
        SigScan("48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 33 C0 89 44 24 ? 0F 57 C0 0F 11 02 48 89 42 ? 48 89 42 ? 48 8D 15"),
        &lambda_ScreenController_registerTabNameBinding
    );
}
