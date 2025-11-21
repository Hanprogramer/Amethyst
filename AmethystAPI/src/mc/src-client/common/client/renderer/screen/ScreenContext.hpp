#pragma once
#include "mc/src-client/common/client/gui/screens/UIScreenContext.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/MeshContext.hpp"

class Tessellator;

#pragma pack(push, 1)
class ScreenContext : public UIScreenContext, public mce::MeshContext {
public:
    std::byte padding40[192 - 40];
    Tessellator& tessellator; // this + 192
};  
#pragma pack(pop)

//static_assert(offsetof(ScreenContext, tessellator) == 192);