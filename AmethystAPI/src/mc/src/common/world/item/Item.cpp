#include "mc/src/common/world/item/Item.hpp"

short Item::getDamageValue(CompoundTag* userData) const
{
    if (userData == nullptr) return 0;
    if (!userData->contains("Damage")) return 0;
    return (short)userData->getInt("Damage");
}

bool Item::hasTag(const HashedString& tag) const
{
    for (const ItemTag& itemTag : mTags) {
        if (itemTag.getHash() == tag.getHash()) {
            return true;
        }
    }

    return false;
}

UseAnim Item::getUseAnim() const
{
    return mUseAnim;
}

const std::string& Item::getRawNameId() const {
    return mRawNameId.getString();
}

void Item::setAllowOffhand(bool allowsOffhand)
{
    mAllowOffhand = allowsOffhand;
}

//
//uint64_t Item::getMaxDamage() const
//{
//    using function = uint64_t(__thiscall*)(const Item*);
//    return reinterpret_cast<function>(this->vtable[33])(this);
// }