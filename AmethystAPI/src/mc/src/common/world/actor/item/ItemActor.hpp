#pragma once
#include <mc/src/common/world/actor/Actor.hpp>
#include <mc/src/common/world/item/ItemStack.hpp>

class ItemActor : public Actor {
public:
	ItemStack mItem;
};

static_assert(offsetof(ItemActor, mItem) == 1096);