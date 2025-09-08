/// @symbolgeneration
#pragma once
#include <amethyst/ModApi.hpp>
#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"

class StartMenuScreenController : public ScreenController {
public:
    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B D9 48 8B 81}
    MINECRAFT void _registerBindings();
};