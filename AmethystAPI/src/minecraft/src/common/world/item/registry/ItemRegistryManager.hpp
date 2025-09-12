/// @symbolgeneration
#pragma once
#include "minecraft/src/common/world/item/registry/ItemRegistryRef.hpp"

class ItemRegistryManager {
public:
    /// @signature {40 53 48 83 EC ? 48 83 3D ? ? ? ? ? 48 8B D9 74}
    static ItemRegistryRef getItemRegistry();
};