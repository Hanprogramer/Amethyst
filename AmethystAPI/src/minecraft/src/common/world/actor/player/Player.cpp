#include <minecraft/src/common/world/actor/player/Player.hpp>
#include <minecraft/src/common/world/actor/player/PlayerInventory.hpp>
#include <minecraft/src/common/world/inventory/transaction/ComplexInventoryTransaction.hpp>
#include <minecraft/src/common/world/entity/components/AbilitiesComponent.hpp>

void Player::prepareRegion(ChunkSource& cs)
{
    using function = decltype(&Player::prepareRegion);
    static auto func = std::bit_cast<function>(this->vtable[190]);
    return (this->*func)(cs);
}

const PlayerInventory& Player::getSupplies() const
{
    return *this->playerInventory;
}

const ItemStack& Player::getSelectedItem() const
{
    return playerInventory->getSelectedItem();
}

PlayerEventCoordinator& Player::getPlayerEventCoordinator() {
    using function = decltype(&Player::getPlayerEventCoordinator);
    auto func = std::bit_cast<function>(this->vtable[244]);
    return (this->*func)();
}

void Player::sendInventoryTransaction(const InventoryTransaction& transaction)
{
    using function = decltype(&Player::sendInventoryTransaction);
    auto func = std::bit_cast<function>(this->vtable[241]);
    return (this->*func)(transaction);
}

void Player::sendComplexInventoryTransaction(std::unique_ptr<ComplexInventoryTransaction> transaction) const
{
    using function = decltype(&Player::sendComplexInventoryTransaction);
    auto func = std::bit_cast<function>(this->vtable[242]);
    return (this->*func)(std::move(transaction));
}

const LayeredAbilities& Player::getAbilities() const
{
    return this->tryGetComponent<AbilitiesComponent>()->mAbilities;
}

GameMode& Player::getGameMode() const
{
    return *this->mGameMode.get();
}
