#include "ItemOwnerNameRegistry.hpp"

void Amethyst::ItemOwnerNameRegistry::RegisterItemOwnerName(const std::string& itemFullName, const std::string& ownerName)
{
    mItemOwnerNames[itemFullName] = ownerName;
}

std::optional<std::string> Amethyst::ItemOwnerNameRegistry::GetItemOwnerName(const std::string& itemFullName) const
{
    auto it = mItemOwnerNames.find(itemFullName);
    if (it != mItemOwnerNames.end()) {
        return it->second;
    }
    return std::nullopt;
}
