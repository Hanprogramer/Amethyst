#pragma once
#include <variant>
#include "minecraft/src/common/world/Container.hpp"
#include "minecraft/src/common/ActorUniqueID.hpp"
#include "minecraft/src/common/world/level/BlockPos.hpp"

class Player;

class ContainerScreenContext {
    Player& mPlayer;
    ContainerType mScreenContainerType;
    std::variant<std::monostate, ActorUniqueID, BlockPos> mOwner;
};