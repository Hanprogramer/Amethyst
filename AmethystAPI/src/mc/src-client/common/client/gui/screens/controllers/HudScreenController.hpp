/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src-client/common/client/gui/screens/controllers/ClientInstanceScreenController.hpp"

class HudScreenController :
	public ClientInstanceScreenController
{
public:
    /** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B E2 48 8B F9 48 89 8D} */
    MC HudScreenController(std::shared_ptr<ClientInstanceScreenModel> model);

    /** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B E2 48 8B F9 48 89 8D} */
    MC static void $constructor(HudScreenController* self, std::shared_ptr<ClientInstanceScreenModel> model);
};