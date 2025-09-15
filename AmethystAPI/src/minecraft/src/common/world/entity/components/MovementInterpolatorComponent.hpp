#pragma once
#include <minecraft/src/common/world/phys/Vec3.hpp>
#include <minecraft/src/common/world/phys/Vec2.hpp>

struct MovementInterpolatorComponent {
    Vec3 mPos;
    Vec2 mRot;
    float mHeadYaw;
    int mPositionSteps;
    int mRotationSteps;
    int mHeadYawSteps;
    bool mInterpolationActive;
};