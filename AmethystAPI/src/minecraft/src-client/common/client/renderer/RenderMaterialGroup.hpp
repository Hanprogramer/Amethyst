#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src/common/AppPlatformListener.hpp>
#include <minecraft/src-deps/renderer/RenderMaterialGroupBase.hpp>
#include "minecraft/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp"

namespace mce {
    class RenderMaterialInfo;
    class RenderMaterialGroup : public mce::RenderMaterialGroupBase, public AppPlatformListener {
    public:
        static RenderMaterialGroup* common;
        static RenderMaterialGroup* switchable;

        mce::MaterialPtr getMaterial(const HashedString& name) {
            return mce::MaterialPtr::MaterialPtr(*this, name);
        }
    };
};