/// @symbolgeneration
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <amethyst/Imports.hpp>
#include "minecraft/src/common/world/containers/ContainerEnumName.hpp"
#include "minecraft/src-client/common/client/gui/screens/controllers/ClientInstanceScreenController.hpp"

enum class UIProfile;
enum class FadeInIconBehavior;
class ClientInstanceScreenModel;
class ItemStackBase;
class ItemStack;
class SlotData;
class SelectedSlotInfo;
class ContainerManagerController;
enum class InteractionModel : int {
    CombinedInventory = 0x0000,
    SeparateInventoryAndHotbar = 0x0001,
};

/// @vptr {0x4CD2850}
class ContainerScreenController :
    public ClientInstanceScreenController
{
public:
    std::byte padding3128[0xD88 - sizeof(ClientInstanceScreenController)];
    std::shared_ptr<ContainerManagerController> mContainerManagerController;
    std::byte padding3144[0x3C0];

    /// @address {0x59D9150}
    MC static std::unordered_map<ContainerEnumName, std::string> ContainerCollectionNameMap;

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B F8 48 8B F2}
    MC ContainerScreenController(std::shared_ptr<ClientInstanceScreenModel> model, InteractionModel interactionModel);

    /// @vidx {0}
    MC virtual ~ContainerScreenController();
    /// @vidx {inherit}
    MC virtual ui::DirtyFlag tick() override;
    /// @vidx {inherit}
    MC virtual void onOpen() override;
    /// @vidx {inherit}
    MC virtual void onLeave() override;
    /// @vidx {inherit}
    MC virtual ui::DirtyFlag handleGameEventNotification(ui::GameEventNotification) override;
    /// @vidx {inherit}
    MC virtual void setAssociatedBlockPos(const BlockPos&) override;
    /// @vidx {inherit}
    MC virtual void setAssociatedEntityUniqueID(ActorUniqueID) override;
    /// @vidx {inherit}
    MC virtual void addStaticScreenVars(Json::Value&) override;
    /// @vidx {inherit}
    MC virtual bool _isStillValid(void) override;
    /// @vidx {inherit}
    MC virtual bool _getGestureControlEnabled() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonADescription() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonXDescription() override;
    /// @vidx {inherit}
    MC virtual std::string _getButtonYDescription() override;
    /// @vidx {53}
    MC virtual void _handleTakeHalf(const std::string&, int);
    /// @vidx {54}
    MC virtual void _handlePlaceAll(const std::string&, int);
    /// @vidx {55}
    MC virtual void _handlePlaceOne(const std::string&, int);
    /// @vidx {56}
    MC virtual void _handleTakePlace(const std::string&, int, bool);
    /// @vidx {57}
    MC virtual void _handleSelectSlot(const std::string&, int);
    /// @vidx {58}
    MC virtual SelectedSlotInfo _getSelectedSlotInfo();
    /// @vidx {59}
    MC virtual void _reevaluateSlotData(SlotData&&);
    /// @vidx {60}
    MC virtual void unknown_60();
    /// @vidx {61}
    MC virtual void unknown_61();
    /// @vidx {62}
    MC virtual void unknown_62();
    /// @vidx {63}
    MC virtual ui::ViewRequest _onContainerSlotHovered(const std::string& collection, int index);
    /// @vidx {64}
    MC virtual ui::ViewRequest _onContainerSlotUnhovered(const std::string& collection, int index);
    /// @vidx {65}
    MC virtual ui::ViewRequest _onContainerSlotSelected(const std::string& collection, int index);
    /// @vidx {66}
    MC virtual ui::ViewRequest _onContainerSlotPressed(const std::string& collection, int index);
    /// @vidx {67}
    MC virtual bool _shouldSwap(const std::string& collectionLhs, int indexLhs, const std::string& collectionRhs, int indexRhs);
    /// @vidx {68}
    MC virtual bool _isTargetSwappable(const std::string& collection, int index);
    /// @vidx {69}
    MC virtual std::string _getCollectionName(UIPropertyBag*);
    /// @vidx {70}
    MC virtual bool _canSplit(const std::string&);
    /// @vidx {71}
    MC virtual void _sendFlyingItem(const ItemStackBase&, const std::string&, int, const std::string&, int, FadeInIconBehavior);
    /// @vidx {72}
    MC virtual void _registerCoalesceOrder() = 0;
    /// @vidx {73}
    MC virtual void _registerAutoPlaceOrder() = 0;
    /// @vidx {74}
    MC virtual void _createItemLockNotification(bool);
    /// @vidx {75}
    MC virtual int _getProgressiveBarDirection(const std::string&, int);
    /// @vidx {76}
    MC virtual void unknown_76();
    /// @vidx {77}
    MC virtual bool _isInCreativeContainer(const std::string&);

// Non-virtuals
public:
    static InteractionModel interactionModelFromUIProfile(UIProfile profile);
};

static_assert(sizeof(ContainerScreenController) == 0x1158);