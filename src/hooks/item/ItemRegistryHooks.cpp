#include "ItemRegistryHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/world/item/Item.hpp>
#include <mc/src/common/world/item/registry/CreativeItemRegistry.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/CraftingScreenController.hpp>
#include <algorithm>
#include <mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp>
#include <mc/src/common/world/containers/ContainerEnumName.hpp>
#include <mc/src/common/world/containers/managers/models/CraftingContainerManagerModel.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src/common/world/item/registry/ItemRegistry.hpp>
#include <mc/src/common/world/containers/ContainerFactory.hpp>
#include <mc/src/common/world/containers/managers/controllers/CreativeContainerController.hpp>
#include <mc/src/common/world/containers/models/FilteredContainerModel.hpp>
#include <mc/src/common/world/containers/FullContainerName.hpp>

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
        Log::Info(" - {} {}, category: {}, padding4: {}, mContainerEnum: {}, padding12: {}", tab.mTabName, tab.mTabFactoryName, (uint32_t)tab.mCategory, tab.padding4, (uint64_t)tab.mContainerEnum, tab.padding12);
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

    //Log::Info("{} offset {}", (uintptr_t)self, offsetof(CraftingScreenController, instance4848));

    /*

    for (auto& state : self->mTabStates) {
        Log::Info("Tab state: {} {}", (uint64_t)state.first, (uint64_t)state.second);
    }*/

    //Log::Info("_tabIndexToCollectionName: {} for tabIdx {}", *res, (int64_t)tabIdx);

    return res;
}

SafetyHookInline _lambda_ScreenController_registerTabNameBinding;

void* lambda_ScreenController_registerTabNameBinding(void* a1, void* a2) {
    uint32_t* something = (uint32_t*)((uintptr_t)a1 + 4680);

    //Log::Info("something: {}", *something); // seems to be some random thing each time for the test tab.

    // construction 2742786064

    std::string* res = _lambda_ScreenController_registerTabNameBinding.call<std::string*, void*, void*>(a1, a2);
    //Log::Info("something res '{}'", *res);

    if (res->size() == 0) {
        //Log::Info("set title to craftingScreen.tab.test");
        *res = "craftingScreen.tab.test";
    }

    return (void*)res;
}

// This function is called sometimes on Keyboard + Mouse, but not everytime you change tab, so i dont think this is actually what handles changing the content.
// Altho it does actually call everytime on controller when you use bumpers to switch category. 
// called with recipe_(XYZ), 0
//SafetyHookInline _CraftingScreenController__focusCollectionItem;
//
//void CraftingScreenController__focusCollectionItem(
//    CraftingScreenController* self,
//    const std::string& item,
//    int unkn1)
//{
//    Log::Info("Focusing collection item: {}, unknown {}", item, unkn1);
//
//    _CraftingScreenController__focusCollectionItem.call<void, CraftingScreenController*, const std::string&, int>(
//        self, item, unkn1);
//}



//SafetyHookInline _CraftingScreenController__showCategoryTab;

// Seems to get called once when the inventory opens, after that wont until screen is closed and reopened
// seems to allways call with someBool = false, someInt = 0
// Called for all categories at once!
//void CraftingScreenController__showCategoryTab(
//    CraftingScreenController* self,
//    const CraftingScreenController::CategoryTabInfo& tabInfo,
//    bool someBool,
//    int someInt)
//{
//    Log::Info(
//        "Showing category tab: {} (factory: {}, category: {}, padding4: {}, padding8: {}), someBool: {}, someInt: {}",
//        tabInfo.mTabName,
//        tabInfo.mTabFactoryName,
//        (uint32_t)tabInfo.mCategory,
//        tabInfo.padding4,
//        tabInfo.padding8,
//        someBool,
//        someInt);
//
//    _CraftingScreenController__showCategoryTab.call<void, CraftingScreenController*, const CraftingScreenController::CategoryTabInfo&, bool, int>(
//        self, tabInfo, someBool, someInt);
//}

SafetyHookInline _CraftingContainerManagerModel__postInit;

ContainerScreenContext* CraftingContainerManagerModel__postInit(CraftingContainerManagerModel* self, ContainerScreenContext* res)
{
    _CraftingContainerManagerModel__postInit.call<ContainerScreenContext*, CraftingContainerManagerModel*, ContainerScreenContext*>(self, res);

    Log::Info("CraftingContainerManagerModel__postInit: {}", (uint64_t)res->mScreenContainerType);
    Level& level = *self->mPlayer.getLevel()->asLevel();

    //ItemRegistryRef itemRegRef = level.getItemRegistry();
    //std::shared_ptr<ItemRegistry> itemReg = itemRegRef._lockRegistry();

    CreativeItemRegistry* creativeItemReg = CreativeItemRegistry::mCurrentRegistry.get();
    
    CreativeItemGroupCategory* testCategory = nullptr;

    if (creativeItemReg) {
        testCategory = creativeItemReg->getCreativeCategory((CreativeItemCategory)8);
        //testCategory = creativeItemReg->getCreativeCategory(CreativeItemCategory::Items);
    }

    ContainerEnumName testTabContainer = (ContainerEnumName)63;
    //ContainerEnumName testTabContainer = ContainerEnumName::RecipeItemsContainer;
    bool isCreativeMode = true;

    //Log::Info("{}", ContainerScreenController::ContainerCollectionNameMap.size());
    for (const auto& test : ContainerScreenController::ContainerCollectionNameMap) {
        Log::Info("{} {}", (uint64_t)test.first, test.second);
    }

    auto testContainerModel = self->_createContainerModel(testTabContainer, testCategory, isCreativeMode, [](const ItemInstance& item, bool someBool) {
        Log::Info("Callback called with {} and {}", item.mItem->mFullName.getString(), someBool);
        return FilterResult::Show;
    });

    //testContainerModel->m

    return res;
}

class ContainerController;

SafetyHookInline _ContainerFactory_createController;

std::shared_ptr<CreativeContainerController> testPanelController = nullptr;

//const std::string& reimplemented_getContainerName(ContainerController* controller) {
//    Assert(!controller->mContainerModel.expired(), "Container model lifetime is managed by controller creation and destruction");
//
//    auto containerModel = controller->mContainerModel.lock();
//    return containerModel->getContainerStringName();
//}

std::shared_ptr<ContainerController> ContainerFactory_createController(std::shared_ptr<ContainerModel> model)
{
    Assert(model != nullptr, "Invalid Model");

    Log::Info("model mContainerStringName, id {}, starting '{}', item source: {}, items: {}, sparse container: {}",
              (uintptr_t)model->mContainerEnumName,
              model->mContainerStringName,
              model->mItemSource.size(),
              model->mItems.size(),
              model->mClientUIContainer == nullptr ? "nullptr" : "exists!");

    if ((uint64_t)model->mContainerEnumName == 63) {
        


        model->mContainerStringName = "recipe_test";
        testPanelController = std::make_shared<CreativeContainerController>(model);

        Log::Info("res: {}, container name: {}", (uintptr_t)testPanelController.get(), testPanelController->getContainerName());

        return testPanelController;
    }

    std::shared_ptr<ContainerController> res = _ContainerFactory_createController.call<std::shared_ptr<ContainerController>>(model);
    
    //if (res.get() != nullptr) {
    //    Log::Info("Others {}", res->getContainerName());
    //}
    //else {
    //    Log::Info("others was nullptr!");
    //}

    /*Log::Info("ContainerFactory::createController with mContainerName as enum name {} and string name '{}', is client side: {}, returned controller ptr: {}", 
        (uintptr_t)model->mContainerEnumName, 
        model->mContainerStringName,
        model->mIsClientSide,
        (uintptr_t)res.get()
    );*/

    //Log::Info("res: {}", (uintptr_t)(res->get()));

    return res;
}

SafetyHookInline _FullContainerName_toString;

std::string FullContainerName_toString(const FullContainerName* self)
{
    Log::Info("FullContainerName_toString: {}", (uint64_t)self->mName);
    // Call the original function
    //std::string result = _FullContainerName_toString.call<std::string, const FullContainerName*>(self);
    //Log::Info("original result {}", result);

    auto& map = ContainerScreenController::ContainerCollectionNameMap;
    auto it = map.find(self->mName);

    //auto it = std::find_if(map.begin(), map.end(),
    //                       [&](const auto& pair) {
    //                           return static_cast<uint64_t>(pair.first) == static_cast<uint64_t>(self->mName);
    //                       });

    if (it != map.end()) {
        Log::Info("FullContainerName::toString() -> {}", it->second);
        return it->second;
    }

    // Handle missing entry gracefully
    Log::Warning("FullContainerName::toString(): Missing entry for key {}", (uint64_t)self->mName);

    // Fallback: call the original function to preserve vanilla behavior
    std::string fallback = "";
    Log::Info("FullContainerName::toString() (fallback) -> {}", fallback);

    return fallback;
}

void CreateItemRegistryHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, serverInitCreativeItemsCallback);
    HOOK(VanillaItems, _addConstructionCategory);
    HOOK(CraftingScreenController, _tabIndexToCollectionName);
    //HOOK(CraftingScreenController, _showCategoryTab);
    //HOOK(CraftingScreenController, _focusCollectionItem);
    HOOK(ContainerFactory, createController);
    //HOOK(FullContainerName, toString);

    VHOOK(CraftingContainerManagerModel, _postInit, this);

    hooks.CreateHookAbsolute(
        _lambda_ScreenController_registerTabNameBinding,
        SigScan("48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 33 C0 89 44 24 ? 0F 57 C0 0F 11 02 48 89 42 ? 48 89 42 ? 48 8D 15"),
        &lambda_ScreenController_registerTabNameBinding
    );

    ContainerEnumName testTabContainer = (ContainerEnumName)63;

    CraftingScreenController::CategoryTabInfo testTab;
    testTab.mCategory = (CreativeItemCategory)8;
    testTab.mTabName = "test_tab";
    testTab.mTabFactoryName = "test_tab_factory";
    testTab.padding4 = 2; // idk made the same as items_tab
    testTab.mContainerEnum = testTabContainer; 
    testTab.padding12 = 4;

    CraftingScreenController::mCategoryTabs.push_back(std::move(testTab));

    ContainerScreenController::ContainerCollectionNameMap.emplace(
        testTabContainer,
        "recipe_test"
    );

    /*for (auto& container : ContainerScreenController::ContainerCollectionNameMap) {
        Log::Info("container enum {} is '{}'", (uint64_t)container.first, container.second);
    }*/
}
