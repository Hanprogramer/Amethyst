/// @symbolgeneration
#pragma once
#include "minecraft/src/common/world/Container.hpp"
#include "minecraft/src/common/ActorUniqueID.hpp"
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include "minecraft/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"

class SparseContainer;

enum class ContainerCategory : int {
    Default = 0x0000,
    PlayerInventory = 0x0001,
    Intermediary = 0x0002,
    Output = 0x0003,
    Unknown = 0x0004,
};

/// @vptr {0x4DE9508}
class ContainerModel : 
	public ContainerContentChangeListener 
{
public:
    const bool mIsClientSide;
    std::string mContainerStringName;
    const ContainerEnumName mContainerEnumName;
    std::vector<std::function<void(int, const ItemStack&, const ItemStack&)>> mOnContainerChangedCallbacks;
    std::function<void(int, const ItemStack&, const ItemStack&)> mPlayerNotificationCallbacks;
    ContainerCategory mContainerCategory;
    std::vector<SlotData> mItemSource;
    SparseContainer* mClientUIContainer;
    std::vector<ItemStack> mItems;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 4C 24 ? 56 57 41 56 48 83 EC ? 48 8B D9 48 8D 05}
    MC ContainerModel(ContainerEnumName, int, ContainerCategory, bool);

    /// @vidx {0}
    MC virtual void containerContentChanged(int);
    /// @vidx {1}
    MC virtual ~ContainerModel();
    /// @vidx {2}
    MC virtual void postInit();
    /// @vidx {3}
    MC virtual void releaseResources();
    /// @vidx {4}
    MC virtual void getContainerSize();
    /// @vidx {5}
    MC virtual void getFilteredContainerSize();
    /// @vidx {6}
    MC virtual void tick(int);
    /// @vidx {7}
    MC virtual void getContainerWeakRef();
    /// @vidx {8}
    MC virtual void getItemStack(int);
    /// @vidx {9}
    MC virtual void getItems();
    /// @vidx {10}
    MC virtual void getItemInstance(int);
    /// @vidx {11}
    MC virtual void getItemStackBase(int);
    /// @vidx {12}
    MC virtual void isItemInstanceBased();
    /// @vidx {13}
    MC virtual void setItem(int, const ItemStack&);
    /// @vidx {14}
    MC virtual void isValid();
    /// @vidx {15}
    MC virtual void isItemFiltered(const ItemStackBase&);
    /// @vidx {16}
    MC virtual void isExpanableItemFiltered(int);
    /// @vidx {17}
    MC virtual void getItemExpandStatus(int);
    /// @vidx {18}
    MC virtual void getItemGroupName(int);
    /// @vidx {19}
    MC virtual void switchItemExpando(int);
    /// @vidx {20}
    MC virtual void isSlotDisabled(int);
    /// @vidx {21}
    MC virtual void _getContainer();
    /// @vidx {22}
    MC virtual void _getContainerOffset();
    /// @vidx {23}
    MC virtual void _init();
    /// @vidx {24}
    MC virtual void _onItemChanged(int, const ItemStack&, const ItemStack&);
};

static_assert(sizeof(ContainerModel) == 0xD0);