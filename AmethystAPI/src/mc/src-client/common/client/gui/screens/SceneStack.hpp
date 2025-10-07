/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"

#include <memory>
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"

class AbstractScene;
class SceneStack : 
    public Bedrock::EnableNonOwnerReferences 
{
public:
    std::vector<std::shared_ptr<AbstractScene>> mScreenStack;

    /// @signature {48 89 54 24 ? 53 48 83 EC ? 48 8B DA C6 44 24 ? ? 0F 57 C0}
    MC void pushScreen(std::shared_ptr<AbstractScene> screen, bool idk);
};