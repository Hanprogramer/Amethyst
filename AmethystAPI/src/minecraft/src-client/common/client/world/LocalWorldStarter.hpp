#pragma once
#include <minecraft/src-client/common/client/world/WorldID.hpp>

namespace World {

class LocalWorldStarter {
public:
    uint64_t startLocalWorld(const World::WorldID& worldId);
};

}