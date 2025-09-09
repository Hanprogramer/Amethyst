#pragma once
#include <string>
#include <minecraft/src/common/world/level/storage/LevelSummary.hpp>

class WorldCreationHelper {
public:
	std::byte padding0[136];
	LevelSettings levelSettings; // 136
	std::string someString;
	uint64_t padding1512;
	PackIdVersion somePackId; // 1528
	LevelSummary levelSummary; // 1656
};
