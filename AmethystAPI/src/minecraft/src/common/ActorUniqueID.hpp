#pragma once
#include <cstdint>

struct ActorUniqueID {
    int64_t rawID;

    ActorUniqueID() : rawID(-1) {}
    ActorUniqueID(int64_t id) : rawID(id) {}    
};