#pragma once
#include <string>
#include <unordered_map>
#include <optional>

namespace Amethyst {
class ItemOwnerNameRegistry {
    std::unordered_map<std::string, std::string> mItemOwnerNames;

public: 
    ItemOwnerNameRegistry() = default;
    ~ItemOwnerNameRegistry() = default;

    ItemOwnerNameRegistry(const ItemOwnerNameRegistry&) = delete;
    ItemOwnerNameRegistry& operator=(const ItemOwnerNameRegistry&) = delete;
    ItemOwnerNameRegistry(ItemOwnerNameRegistry&&) = delete;
    ItemOwnerNameRegistry& operator=(ItemOwnerNameRegistry&&) = delete;

    /*
     * Registers an owner name for the given item full name.
     * Observe that if an owner name is already registered for the item, it will be overwritten.
     * itemFullName should be in the format "modid:itemname" (e.g. "minecraft:diamond_sword").
     */
    void RegisterItemOwnerName(const std::string& itemFullName, const std::string& ownerName);

    /*
     * Gets the registered item owner name for the given item full name, if it exists.
     * Returns std::nullopt if no owner name is registered for the item.
     * itemFullName should be in the format "modid:itemname" (e.g. "minecraft:diamond_sword").
     */
    std::optional<std::string> GetItemOwnerName(const std::string& itemFullName) const;
};
}