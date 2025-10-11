#pragma once
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>

class CreativeItemRegistry;

// All of the hooks to do with (creative) item registration.

void CreateItemRegistryHooks();

void RegisterCustomCategories(CreativeItemRegistry* creative, ItemRegistryRef ref);