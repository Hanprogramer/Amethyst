/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class BaseGameVersion;
class Experiments;
class ItemRegistryRef;
class CreativeItemRegistry;
class ActorInfoRegistry;
class BlockDefinitionGroup;


class VanillaItems {
public:
    /// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24}
    MC static void registerItems(void* a1, const ItemRegistryRef itemRegistry, const BaseGameVersion* baseGameVersion, const Experiments* experiments);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E8 4C 8B F2 48 8B D9}
    MC static void _addItemsCategory(CreativeItemRegistry* creativeItemRegistry, ItemRegistryRef registry, const BaseGameVersion& version, const Experiments& experiments);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1 49 8B F8 4C 8B F9 48 89 4D}
    MC static void serverInitCreativeItemsCallback(ItemRegistryRef ref, ActorInfoRegistry* actorInfo, BlockDefinitionGroup* blockDefs, CreativeItemRegistry* creativeReg, const BaseGameVersion& version, const Experiments& experiments);

    /// @signature {48 89 5C 24 ? 48 89 54 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8}
    MC static void _addConstructionCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);
};