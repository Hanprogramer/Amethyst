#pragma once
#include <optional>
#include <amethyst/game/capabilities/BlockCapability.hpp>
#include <amethyst/game/capabilities/IItemHandler.hpp>
#include <mc/src/common/world/Facing.hpp>

namespace Amethyst {

class Capabilities {
public:
	class ItemHandler {
	public:
		BlockCapability<IItemHandler, std::optional<FacingID>> BLOCK;

	public:
		ItemHandler(ItemHandler&&) = delete;
		ItemHandler& operator=(ItemHandler&&) = delete;
		
		ItemHandler(const ItemHandler&) = delete;
        ItemHandler& operator=(const ItemHandler&) = delete;

		// MODS DO NOT NEED TO CONSTRUCT THIS
		ItemHandler();
	};

	ItemHandler itemHandler;

public:
	// MODS DO NOT NEED TO CONSTRUCT THIS
	Capabilities() = default;

	Capabilities(Capabilities&&) = delete;
    Capabilities& operator=(Capabilities&&) = delete;

	Capabilities(const Capabilities&) = delete;
    Capabilities& operator=(const Capabilities&) = delete;
};
}