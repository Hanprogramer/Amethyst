/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include "minecraft/src-client/common/client/gui/screens/SceneStack.hpp"

class SceneFactory {
public:
    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B EA 33 F6}
    MC Bedrock::NonOwnerPointer<SceneStack> getCurrentSceneStack();
};
