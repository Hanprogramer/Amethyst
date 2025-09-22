#pragma once
#include <minecraft/src/common/world/actor/player/Player.hpp>

class ServerPlayer : public Player {
public:
    std::byte padding7584[152];
    char mContainerCounter;

    ContainerID nextContainerId() {
        auto nextContainerId = mContainerCounter + 1;
        if (nextContainerId >= (char)ContainerID::CONTAINER_ID_LAST)
            nextContainerId = (char)ContainerID::CONTAINER_ID_FIRST;
        mContainerCounter = nextContainerId;
        return ContainerID(nextContainerId);
    }
};

static_assert(offsetof(ServerPlayer, mContainerCounter) == 7744);