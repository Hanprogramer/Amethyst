#include "ItemOwnerNameRegistry.hpp"

void Amethyst::ItemOwnerNameRegistry::RegisterItemOwnerNameForNamespace(const std::string& namespaceName, const std::string& ownerName)
{
    mNamespaceOwnerNames[namespaceName] = ownerName;
}

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

std::optional<std::string> Amethyst::ItemOwnerNameRegistry::GetItemOwnerNameByNamespace(const std::string& namespaceName) const
{
    auto it = mNamespaceOwnerNames.find(namespaceName);
    if (it != mNamespaceOwnerNames.end()) {
        return it->second;
    }
    return std::nullopt;
}
