/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include "mc/src/common/world/level/block/ActorBlock.hpp"

/// @vptr {0x4E37018}
class ChestBlock : 
    public ActorBlock 
{
public:
    MC static uintptr_t $vtable_for_this;

    enum class ChestType : int {
        Default = 0,
        Trapped = 1,
        Other = 2
    };
    
    ChestType mChestType;
    
    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 4C 8B 15}
    MC ChestBlock(const std::string& nameId, short id, ChestType type, MaterialType materialType);
    
public:
    /// @vidx {inherit}
    MC virtual ~ChestBlock() override;
    /// @vidx {inherit}
    MC virtual bool canProvideSupport(const Block& block, unsigned char face, BlockSupportType type) const override;
    /// @vidx {inherit}
    MC virtual bool isContainerBlock() const override;
    /// @vidx {inherit}
    MC virtual bool isSignalSource() const override;
    /// @vidx {inherit}
    MC virtual bool shouldConnectToRedstone(BlockSource&, const BlockPos&, Direction::Type) const override;
    /// @vidx {inherit}
    MC virtual bool dispense(BlockSource& region, Container& container, int slot, const Vec3& pos, unsigned char face) const override;
    /// @vidx {inherit}
    MC virtual void onMove(BlockSource& region, const BlockPos& from, const BlockPos& to) const override;
    /// @vidx {inherit}
    MC virtual bool detachesOnPistonMove(BlockSource&, BlockPos const&) const override;
    /// @vidx {inherit}
    MC virtual void setupRedstoneComponent(BlockSource& region, const BlockPos& pos) const override;
    /// @vidx {inherit}
    MC virtual bool breaksFallingBlocks(const Block& block, BaseGameVersion version) const override;
    /// @vidx {inherit}
    MC virtual bool getSecondPart(const IConstBlockSource&, const BlockPos&, BlockPos&) const override;
    /// @vidx {inherit}
    MC virtual bool hasComparatorSignal() const override;
    /// @vidx {inherit}
    MC virtual int getComparatorSignal(BlockSource& region, const BlockPos& pos, const Block& block, unsigned char dir) const override;
    /// @vidx {inherit}
    MC virtual unsigned char getMappedFace(unsigned char face, const Block& block) const override;
    /// @vidx {inherit}
    MC virtual BlockLegacy& init() override;
    /// @vidx {inherit}
    MC virtual void onRemove(BlockSource& region, const BlockPos& pos) const override;
    /// @vidx {inherit}
    MC virtual void onPlace(BlockSource& region, const BlockPos& pos) const override;
    /// @vidx {inherit}
    MC virtual bool isInteractiveBlock() const override;
    /// @vidx {inherit}
    MC virtual bool use(Player& player, const BlockPos& pos, unsigned char face) const override;
};



// 1.21.0.3
// static_assert(sizeof(ChestBlock) == 992); its fun, the editor doesn't complain, the compiler complains but the game works file xD