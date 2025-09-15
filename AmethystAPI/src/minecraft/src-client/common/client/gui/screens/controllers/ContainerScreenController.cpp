#include "minecraft/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"
#include "minecraft/src-client/common/client/gui/screens/models/ClientInstanceScreenModel.hpp"

InteractionModel ContainerScreenController::interactionModelFromUIProfile(UIProfile profile)
{
    return profile == UIProfile::Classic ? InteractionModel::SeparateInventoryAndHotbar : InteractionModel::CombinedInventory;
}