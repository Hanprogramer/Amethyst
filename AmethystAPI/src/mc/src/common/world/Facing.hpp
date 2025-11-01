#pragma once
#include <format>

namespace Facing {
    enum class Name : unsigned char {
        DOWN,
        UP,
        NORTH,
        SOUTH,
        WEST,
        EAST,
        MAX
    };

	static const Facing::Name DIRECTIONS[6] = {
		Facing::Name::DOWN,
		Facing::Name::UP,
		Facing::Name::NORTH,
		Facing::Name::SOUTH,
		Facing::Name::WEST,
		Facing::Name::EAST
	};

	enum class Axis : int {
		X = 0,
		Y = 1,
		Z = 2,
		Count = 3
	};

	inline int choose(Axis axis, int x, int y, int z) {
		switch (axis) {
			case Axis::X: return x;
			case Axis::Y: return y;
			case Axis::Z: return z;
			default: std::unreachable();
		}
	}

    static Facing::Name getOpposite(Facing::Name face);
    static Facing::Name getClockWise(Facing::Name face);
    static Facing::Name getCounterClockWise(Facing::Name face);
    static float getYAngle(Facing::Name face);

	// Axis direction is technically not actually a type in mc, but seemed useful enough to have
	enum class AxisDirection : int {
        POSITIVE = 1,
        NEGATIVE = -1
    };

	inline AxisDirection getAxisDirection(Name face) {
        switch (face) {
            case Name::DOWN:  return AxisDirection::NEGATIVE;
            case Name::UP:    return AxisDirection::POSITIVE;
            case Name::NORTH: return AxisDirection::NEGATIVE;
            case Name::SOUTH: return AxisDirection::POSITIVE;
            case Name::WEST:  return AxisDirection::NEGATIVE;
            case Name::EAST:  return AxisDirection::POSITIVE;
            default: std::unreachable();
        }
    }


};

typedef Facing::Name FacingID;


template <>
struct std::formatter<FacingID> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // No custom specifiers
    }

    template <typename FormatContext>
    auto format(const FacingID& face, FormatContext& ctx) const {
        std::string_view name;
        switch (face) {
            case FacingID::DOWN:  name = "down";  break;
            case FacingID::UP:    name = "up";    break;
            case FacingID::NORTH: name = "north"; break;
            case FacingID::SOUTH: name = "south"; break;
            case FacingID::WEST:  name = "west";  break;
            case FacingID::EAST:  name = "east";  break;
            default:              name = "unknown"; break;
        }
        return std::format_to(ctx.out(), "{}", name);
    }
};