/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
// #include <mc/src/common/world/inventory/InventoryOptions.hpp>

#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/inventory/InventoryOptions.hpp>
#include <mc/src/common/world/containers/ContainerEnumName.hpp>
#include <mc/src/common/world/item/ItemInstance.hpp>

enum class CategoryTabState : uint32_t {
    Test
};

class CraftingScreenController {
public:
    struct CategoryTabInfo {
    public:
        // For construction_tab these two fields were: 4294967297 ((padding4) 0x1000 , (mCategory) 00001) 
        CreativeItemCategory mCategory; 
        uint32_t padding4; // no idea what this is
        ContainerEnumName mContainerEnum; // same with this one.  
        uint32_t padding12; // split from padding 8 to see if it makes more sense
        std::string mTabName;
        std::string mTabFactoryName;
    };

public:
    std::byte padding0[4536]; 
    ItemInstance instance4536;
    std::byte padding4672[4848 - 4672];
    ItemInstance instance4848;
    uint64_t padding4984;

    std::unordered_map<InventoryLeftTabIndex, CategoryTabState> mTabStates;

    /// @address {0x59BF778}
    MC static std::vector<CategoryTabInfo> mCategoryTabs;

    /// @signature {48 89 5C 24 ? 44 89 44 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 41 8B F8}
    MC std::string _tabIndexToCollectionName(InventoryLeftTabIndex tabIdx) const;

    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 45 8B F8 48 8B DA 4C 8B F1}
    MC void _focusCollectionItem(const std::string& item, int unkn1);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 8B E1}
    MC void _showCategoryTab(const CategoryTabInfo& tabInfo, bool someBool, int someInt);
};

static_assert(offsetof(CraftingScreenController, mTabStates) == 4992);