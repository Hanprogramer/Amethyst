#pragma once
#include "minecraft/src/common/world/actor/Actor.hpp"
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include "minecraft/src/common/ActorUniqueID.hpp"

class CompassSpriteCalculator {
public:
    int mFrame;
    float mRot;
    float mRotA;
    const std::function<BlockPos(const BlockSource*, Actor*)> mTargetToPointTo;
    const std::function<bool(const BlockSource*, Actor*)> mIsPointingAtTarget;
};

class MobAnimationComponent;
class MobHurtTimeComponent;

class BuiltInMobComponents {
public:
    gsl::not_null<MobAnimationComponent*> mMobAnimationComponent;
    gsl::not_null<MobHurtTimeComponent*> mMobHurtTimeComponent;
};

class ClockSpriteCalculator {
public:
    int mFrame;
    float mRot;
    float mRotA;
};

enum MobSpawnMethod : int32_t {
    // idk
};

class Mob : public Actor {
public:
    int mHurtDuration;
    float mHurtDir;
    float mOTilt;
    float mTilt;
    CompassSpriteCalculator mCompassSpriteCalc;
    CompassSpriteCalculator mRecoveryCompassSpriteCalc;
    ClockSpriteCalculator mClockSpriteCalc;
    float mAttackAnim;
    bool mSwinging;
    int mSwingTime;
    int mDeathTime;
    float mMovementComponentCurrentSpeed;
    bool mSurfaceMob;
    bool mNaturallySpawned;
    bool mWantsToBeJockey;
    bool mSpawnedXP;
    BuiltInMobComponents mBuiltInMobComponents;
    ActorUniqueID mCaravanHead;
    ActorUniqueID mCaravanTail;
    float mOAttackAnim;
    bool mHasBoundOrigin;
    BlockPos mBoundOrigin;
    std::optional<bool> mActuallyDoKnockbackOrNotReallyBadHackDoNotUse;
    MobSpawnMethod mSpawnMethod;
    bool mCreateAiOnReload;
    ActorUniqueID mTargetCaptainId;

public:
    // 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 48 8B 01 0F B6 DA BA
    void setSprinting(bool isSprinting);

    // virtuals
    void swing(); 

    float getAttackAnim(float a) const {
        float delta = mAttackAnim - mOAttackAnim;
        if (delta < 0.0f) delta += 1.0f;
        return (delta * a) + mOAttackAnim;
    }
};

// 1.21.0.3
static_assert(sizeof(Mob) == 1512);