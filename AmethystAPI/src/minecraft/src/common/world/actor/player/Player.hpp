/// @symbolgeneration
#pragma once
#include <memory>
#include "minecraft/src/common/world/actor/Mob.hpp"
#include <minecraft/src/common/world/item/ItemGroup.hpp>
#include <minecraft/src/common/world/inventory/transaction/InventoryTransactionManager.hpp>
#include <minecraft/src/common/world/actor/player/SerializedSkin.hpp>
#include <minecraft/src/common/world/actor/player/PlayerInventory.hpp>

class ChunkSource;
class ItemStackNetManagerBase;
class PlayerEventCoordinator;
class InventoryTransaction;
class ComplexInventoryTransaction;
class LayeredAbilities;
class IContainerManager;
class GameMode;
class ServerPlayer;
class LocalPlayer;

#pragma pack(push, 8)
/// @vptr {0x4DBEEB8}
class Player : public Mob {
public:
    /* this + 1512 */ std::byte padding1512[360];
    /* this + 1872 */ std::shared_ptr<IContainerManager> mContainerManager;
    /* this + 1888 */ PlayerInventory* playerInventory;
    /* this + 1896 */ std::byte padding1896[1920 - 1896];
    /* this + 1920 */ SerializedSkin mSkin;
    /* this + 2528 */ std::byte padding2528[3288 - 2528];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    ///* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
    /* this + 3432 */ std::byte padding3432[3736 - 3432];
    /* this + 3736 */ InventoryTransactionManager mTransactionManager;
    /* this + 3784 */ std::unique_ptr<GameMode> mGameMode;
    /* this + 3792 */ std::byte padding3792[2680];
    /* this + 6472 */ std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;
    /* this + 6480 */ std::byte padding6480[1112];

    // 101% accurate parameters lmao
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 89 4C 24 ? 4C 89 44 24}
    MC void $constructor(Player* self, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, void* a11, void* a12, void* a13, void* a14);

    MC static uintptr_t $vtable_for_this;

    /// @vidx {inherit}
    MC virtual void aiStep() override;

    /* virtuals */
    void prepareRegion(ChunkSource& cs);
    const PlayerInventory& getSupplies() const;
    const ItemStack& getSelectedItem() const;
    PlayerEventCoordinator& getPlayerEventCoordinator(); 

    void sendInventoryTransaction(const InventoryTransaction& transaction); 
    void sendComplexInventoryTransaction(std::unique_ptr<ComplexInventoryTransaction>) const; 
    int getItemUseDuration() const;
    void sendNetworkPacket(Packet&);

    // non virtuals
    const LayeredAbilities& getAbilities() const;
    GameMode& getGameMode() const;
    bool canUseOperatorBlocks() const;
    void updateSkin(const SerializedSkin& skin, int clientSubID);
    void setPlayerGameType(GameType gameType);

    void setContainerManagerModel(std::shared_ptr<IContainerManager> manager);
    std::weak_ptr<IContainerManager> getContainerManagerModel() const;

    const ServerPlayer* getServerPlayer() const;
    const LocalPlayer* getLocalPlayer() const;
    ServerPlayer* getServerPlayer();
    LocalPlayer* getLocalPlayer();
};
#pragma pack(pop)   


// 1.21.0.3
//static_assert(offsetof(Player, mItemStackNetManager) == 6472);
static_assert(offsetof(Player, playerInventory) == 1888);
//static_assert(offsetof(Player, mTransactionManager) == 3736);
//static_assert(sizeof(Player) == 7592);  


// idk version
//static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 