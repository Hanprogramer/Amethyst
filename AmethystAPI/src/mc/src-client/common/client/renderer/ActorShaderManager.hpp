#pragma once
#include <mc/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp>
#include <mc/src-deps/core/math/Color.hpp>

class Actor;

class ActorShaderManager {
public:
    /* this + 8  */ mce::MaterialPtr mEntityMaterial;
    /* this + 24 */ mce::MaterialPtr mTransparentEntityMaterial;
    /* this + 40 */ mce::MaterialPtr mStaticMaterial;

    virtual ~ActorShaderManager();
    virtual mce::Color _getOverlayColor(Actor&, float) const;
};