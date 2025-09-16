/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src/common/world/containers/managers/IContainerManager.hpp"
// NOT WIP

/// @vptr {0x4DE9970}
class ContainerManagerModel :
	public IContainerManager
{
public:
    std::byte padding8[0xD0];

    /// @signature {48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 4C 89 41}
    MC ContainerManagerModel(ContainerID id, Player& player);

    /// @vidx {0}
    MC virtual ~ContainerManagerModel();
    /// @vidx {1}
    MC virtual ContainerID getContainerId();
    /// @vidx {2}
    MC virtual void setContainerId(ContainerID id);
    /// @vidx {3}
    MC virtual ContainerType getContainerType();
    /// @vidx {4}
    MC virtual void setContainerType(ContainerType type);
    /// @vidx {5}
    MC virtual void serverInitItemStackIds();

    virtual std::vector<ItemStack> getItemCopies() = 0;
    virtual void setSlot(int slot, const ItemStack& stack, bool) = 0;
    virtual const ItemStack& getSlot(int slot) = 0;
    virtual void setData(int, int) = 0;
    virtual void broadcastChanges() = 0;

    /// @vidx {11}
    MC virtual void debitPlayerLevels(int amount);
    /// @vidx {12}
    MC virtual bool isCreativeMode();
    /// @vidx {13}
    MC virtual bool isClientSide();
    /// @vidx {14}
    MC virtual bool isServerAuthoritative();
    /// @vidx {15}
    MC virtual bool isValid(float);
    /// @vidx {16}
    MC virtual int tick();

    virtual void _postInit() = 0;

// Non-virtuals
public:

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8B E9}
    MC void postInit();
};

static_assert(sizeof(ContainerManagerModel) == 0xD8);