/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/world/Container.hpp"

class ListTag;
class SemVersion;
class Level;

/// @vptr {0x4DE56F8}
class FillingContainer : public Container {
public:
    std::vector<ItemStack> mItems;
    Player* mPlayer;

public:
    FillingContainer(Player* player, int size, ContainerType type);

public:
    /// @vidx {inherit}
    MC virtual ~FillingContainer();
    /// @vidx {inherit}
    MC virtual void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) override;
    /// @vidx {inherit}
    MC virtual const ItemStack& getItem(int slot) const override;
    /// @vidx {inherit}
    MC virtual void setItem(int slot, const ItemStack& item) override;
    /// @vidx {inherit}
    MC virtual void setItemWithForceBalance(int, const ItemStack&, bool) override;
    /// @vidx {inherit}
    MC virtual void removeItem(int, int) override;
    /// @vidx {inherit}
    MC virtual int getContainerSize() const override;
    /// @vidx {inherit}
    MC virtual int getMaxStackSize() const override;
    /// @vidx {inherit}
    MC virtual void startOpen(Player&) override;
    /// @vidx {42}
    MC virtual void add(ItemStack& item);
    /// @vidx {43}
    MC virtual bool canAdd(const ItemStack& item);
    /// @vidx {44}
    MC virtual void clearSlot(int slot);
    /// @vidx {45}
    MC virtual void clearInventory(int size);
    /// @vidx {46}
    MC virtual void load(const ListTag& tag, const SemVersion& version, Level&);
};

// 1.21.0.3
static_assert(sizeof(FillingContainer) - sizeof(Container) == 32);