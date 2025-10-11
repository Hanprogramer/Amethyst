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

    Log::Info("tabs size {}", CraftingScreenController::mCategoryTabs.size());

    for (auto& tab : CraftingScreenController::mCategoryTabs) {
        Log::Info(" - {} {}, category: {}, padding4: {}, mContainerEnum: {}, padding12: {}", tab.mTabName, tab.mTabFactoryName, (uint32_t)tab.mCategory, tab.padding4, (uint64_t)tab.mContainerEnum, tab.padding12);
    }

    Log::Info("VanillaItems::addConstructionCategory! {}", (uintptr_t)Item::mActiveCreativeItemCategory);
    Item::mActiveCreativeItemCategory = creative->newCreativeCategory("Test", (CreativeItemCategory)8);
    Item::mActiveCreativeGroupInfo = nullptr;

    const Block* testBlock = BlockTypeRegistry::getDefaultBlockState("fx_tests:test_block");
    Item::addCreativeItem(ref, *testBlock);

    //ItemInstance instance = ItemInstance("fx_tests:example_item", 1, 0, nullptr);
    //Item::addCreativeItem(ref, instance);
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

struct lambdaArgs {
    CraftingScreenController* self;
};

void* lambda_ScreenController_registerTabNameBinding(lambdaArgs* a1, void* a2)
{
    

    Log::Info("lambda_ScreenController_registerTabNameBinding something {}, tab states size {}", a1->self->something, a1->self->mTabStates.size());

    //for (auto& tabState : a1->self->mTabStates) {
    //    Log::Info("tabState idx {} is {}", (uint32_t)tabState.first, (uint32_t)tabState.second);
    //}

    //Log::Info("something: {}", *something); // seems to be some random thing each time for the test tab.

    // construction 2742786064

    std::string* res = _lambda_ScreenController_registerTabNameBinding.call<std::string*, void*, void*>(a1, a2);
    //Log::Info("something res '{}'", *res);

    if (res->size() == 0) {
        //Log::Info("set title to craftingScreen.tab.test");
        *res = "craftingScreen.tab.test";
    }

    //std::string collectionName = a1->self->_tabIndexToCollectionName((InventoryLeftTabIndex)a1->self->something);
    //const ItemStack& firstStack = a1->self->mContainerManagerController->getItemStack(collectionName, 0);
    //Log::Info("Tab {} first stack {}", collectionName, firstStack.toDebugString());

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



SafetyHookInline _CraftingScreenController__showCategoryTab;

 //Seems to get called once when the inventory opens, after that wont until screen is closed and reopened
 //seems to allways call with someBool = false, someInt = 0
 //Called for all categories at once!
void CraftingScreenController__showCategoryTab(
    CraftingScreenController* self,
    const CraftingScreenController::CategoryTabInfo& tabInfo,
    bool someBool,
    int someInt)
{
    Log::Info(
        "Showing category tab: {} (factory: {}, category: {}, padding4: {}, container enum: {}), someBool: {}, someInt: {}",
        tabInfo.mTabName,
        tabInfo.mTabFactoryName,
        (uint32_t)tabInfo.mCategory,
        tabInfo.padding4,
        (uint64_t)tabInfo.mContainerEnum,
        someBool,
        someInt);

    _CraftingScreenController__showCategoryTab.call<void, CraftingScreenController*, const CraftingScreenController::CategoryTabInfo&, bool, int>(
        self, tabInfo, someBool, someInt);
}

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
    //for (const auto& test : ContainerScreenController::ContainerCollectionNameMap) {
    //    Log::Info("{} {}", (uint64_t)test.first, test.second);
    //}

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

    Log::Info("createController model, id {}, string name '{}', item source: {}, items: {}, sparse container: {}",
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

SafetyHookInline _CraftingScreenController__registerBindings;

void CraftingScreenController__registerBindings(CraftingScreenController* self) {
    _CraftingScreenController__registerBindings.call<void>(self);

    self->bindBool(
        "#is_left_tab_test",
        [self]() {
            return self->something == 8; 
        }, 
        []() { return true; }
    );
}

void CreateItemRegistryHooks()
{
    Log::Info("CreateItemRegistryHooks");

    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, _addItemsCategory);
    HOOK(VanillaItems, _addCommandOnlyCategory);
    HOOK(VanillaItems, _addEquipmentCategory);
    HOOK(VanillaItems, _addNatureCategory);
    HOOK(VanillaItems, _addConstructionCategory);
    HOOK(CraftingScreenController, _tabIndexToCollectionName);
    HOOK(CraftingScreenController, _showCategoryTab);
    HOOK(ContainerFactory, createController);

    HOOK(CraftingScreenController, _registerBindings);

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
    testTab.padding4 = 5; // idk random number
    testTab.mContainerEnum = testTabContainer; 
    testTab.padding12 = 0; // same as all other tabs

    CraftingScreenController::mCategoryTabs.push_back(std::move(testTab));

    ContainerScreenController::ContainerCollectionNameMap.emplace(
        testTabContainer,
        "recipe_test"
    );

    /*for (auto& container : ContainerScreenController::ContainerCollectionNameMap) {
        Log::Info("container enum {} is '{}'", (uint64_t)container.first, container.second);
    }*/
}
