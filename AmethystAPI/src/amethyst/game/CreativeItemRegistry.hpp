#pragma once
#include <mc/src/common/world/item/CreativeItemCategory.hpp>

class Block;
class ItemInstance;

namespace Amethyst {

/**
 * An instance of a creative item category, each category is a tab in the creative inventory
 */
class CreativeCategory {
public:
    void AddCreativeItem(const Block& block);
    void AddCreativeItem(const ItemInstance& item);
};

/**
 * A registry for adding creative items to the game without worrying about timings
 * eventually will support creating custom item categories too.
 */
class CreativeItemRegistry {
public:
    CreativeCategory& GetVanillaCategory(CreativeItemCategory vanillaCategory) const;
};

}