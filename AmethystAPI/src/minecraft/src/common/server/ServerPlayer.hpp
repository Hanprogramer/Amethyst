#pragma once
#include <minecraft/src/common/world/actor/player/Player.hpp>

class ServerPlayer : public Player {
public:
    std::byte padding7584[152];
    char mContainerCounter;
};

static_assert(offsetof(ServerPlayer, mContainerCounter) == 7744);