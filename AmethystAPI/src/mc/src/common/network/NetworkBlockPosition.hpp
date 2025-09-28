#pragma once
#include <mc/src/common/world/level/BlockPos.hpp>

class NetworkBlockPosition : public BlockPos {
public:
    NetworkBlockPosition(const BlockPos& other) : BlockPos(other) {}
};