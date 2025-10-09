#pragma once
#include "mc/src/common/world/item/AuxDataBlockItem.hpp"

class ShulkerBoxBlockItem : public AuxDataBlockItem {
public:
    // @vidx {inherit}
    virtual void appendFormattedHovertext(const ItemStackBase& stack, Level& level, std::string& hovertext, bool showCategory) const override;
};