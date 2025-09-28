#pragma once
#include "mc/src/common/world/item/ItemStackBase.hpp"

class ItemStackBase;

class ItemInstance : public ItemStackBase {
public:
    ItemInstance(const ItemStackBase& base) : ItemStackBase(base) {
        static uintptr_t** address = (uintptr_t**)AddressFromLeaInstruction(SigScan("48 8D 05 ? ? ? ? 49 89 06 48 8D 15"));
        vtable = address;
    }
};

