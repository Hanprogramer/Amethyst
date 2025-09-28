/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/world/item/Item.hpp"

class BlockItem : public Item {
public:
    virtual bool isDestructive(int) const override;
    virtual bool isValidAuxValue(int value) const override;
    virtual std::string buildDescriptionId(const ItemDescriptor&, const CompoundTag*) const override;
    virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase&, int, bool) const override;
    virtual Brightness getLightEmission(int) const override;
    virtual int getIconYOffset() const override;
protected:
    virtual bool _calculatePlacePos(ItemStackBase& unk0, Actor& unk1, FacingID& unk2, BlockPos& unk3) const override;
    virtual InteractionResult _useOn(ItemStack& unk0, Actor& unk1, BlockPos unk2, FacingID unk3, const Vec3& unk4) const override;

public:
    /// @signature {40 53 55 56 57 41 56 48 81 EC ? ? ? ? 49 8B F9 48 8B EA}
    MC BlockItem(const std::string& nameId, short mId, const HashedString& unknown);
};