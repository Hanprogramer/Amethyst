#include <mc/src/common/world/Facing.hpp>
#include <stdexcept>
#include "Facing.hpp"
#include <mc/src/common/world/level/BlockPos.hpp>

BlockPos Facing::getOffset(Facing::Name face) 
 {
	switch (face) {
		case Name::DOWN:  return BlockPos(0, -1, 0);
		case Name::UP:    return BlockPos(0, 1, 0);
		case Name::NORTH: return BlockPos(0, 0, -1);
		case Name::SOUTH: return BlockPos(0, 0, 1);
		case Name::WEST:  return BlockPos(-1, 0, 0);
		case Name::EAST:  return BlockPos(1, 0, 0);
		default: std::unreachable();
	}
}

Facing::Name Facing::getOpposite(Facing::Name face)
{
    switch (face) {
    case FacingID::NORTH:
        return FacingID::SOUTH;

    case FacingID::SOUTH:
        return FacingID::NORTH;

    case FacingID::WEST:
        return FacingID::EAST;

    case FacingID::EAST:
        return FacingID::WEST;

    case FacingID::UP:
        return FacingID::DOWN;

    case FacingID::DOWN:
        return FacingID::UP;

    default:
        std::unreachable();
    }
}

Facing::Name Facing::getClockWise(Facing::Name face)
{
    switch (face) {
    case FacingID::NORTH:
        return FacingID::EAST;

    case FacingID::SOUTH:
        return FacingID::WEST;

    case FacingID::WEST:
        return FacingID::NORTH;

    case FacingID::EAST:
        return FacingID::SOUTH;

    case FacingID::UP:
        return FacingID::UP;

    case FacingID::DOWN:
        return FacingID::DOWN;

    default:
        std::unreachable();
    }
}

Facing::Name Facing::getCounterClockWise(Facing::Name face)
{
    switch (face) {
    case FacingID::NORTH:
        return FacingID::WEST;

    case FacingID::SOUTH:
        return FacingID::EAST;

    case FacingID::WEST:
        return FacingID::SOUTH;

    case FacingID::EAST:
        return FacingID::NORTH;

    case FacingID::UP:
        return FacingID::UP;

    case FacingID::DOWN:
        return FacingID::DOWN;

    default:
        std::unreachable();
    }
}

float Facing::getYAngle(Facing::Name face)
{
    switch (face) {
    case FacingID::NORTH:
        return 0.0f;

    case FacingID::SOUTH:
        return 180.0f;

    case FacingID::WEST:
        return 270.0f;

    case FacingID::EAST:
        return 90.0f;

    case FacingID::UP:
        return 0.0f;

    case FacingID::DOWN:
        return 0.0f;

    default:
        std::unreachable();
    }
}
