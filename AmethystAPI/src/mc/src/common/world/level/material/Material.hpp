#pragma once
#include "mc/src/common/world/level/material/MaterialType.hpp"

class Material {
public:
    MaterialType mType;
    bool mNeverBuildable;
    bool mAlwaysDestroyable;
    bool mLiquid;
    float mTranslucency;
    bool mBlocksMotion;
    bool mBlocksPrecipitation;
    bool mSolid;
    bool mSuperHot;

    bool isLiquid() const
    {
        return mLiquid;
    }
};