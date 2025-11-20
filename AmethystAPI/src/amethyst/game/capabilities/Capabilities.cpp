#pragma once
#include "amethyst/game/capabilities/Capabilities.hpp"
#include "Capabilities.hpp"

Amethyst::Capabilities::ItemHandler::ItemHandler() 
	: BLOCK("item_handler") {
		BLOCK.createSided("item_handler");
	}