///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <optional>
#include <bitset>
#include <memory>
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
class BodyControl;

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
    bleh
};

#pragma pack(push, 8)
/// @vptr {0x4DE88C8}
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

    MC static uintptr_t $vtable_for_this; 

public:
    // virtuals
    /*void setSprinting(bool isSprinting);

    void swing(); 

    float getAttackAnim(float a) const {
        float delta = mAttackAnim - mOAttackAnim;
        if (delta < 0.0f) delta += 1.0f;
        return (delta * a) + mOAttackAnim;
    }

    void aiStep();*/
    
    /**@vidx {2}*/
    virtual bool hasComponent(const HashedString& unk0) const override;

    /**@vidx {3}*/
    virtual void outOfWorld() override;

    /**@vidx {4}*/
    virtual void reloadHardcoded(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {5}*/
    virtual void reloadHardcodedClient(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {6}*/
    virtual void initializeComponents(ActorInitializationMethod unk0, const VariantParameterList& unk1) override;

    /**@vidx {9}*/
    virtual void _doInitialMove() override;

    /**@vidx {15}*/
    virtual float getInterpolatedBodyRot(float unk0) const override;

    /**@vidx {16}*/
    virtual float getInterpolatedHeadRot(float unk0) const override;

    /**@vidx {17}*/
    virtual float getInterpolatedBodyYaw(float unk0) const override;

    /**@vidx {18}*/
    virtual float getYawSpeedInDegreesPerSecond() const override;

    /**@vidx {21}*/
    virtual void blockedByShield(const ActorDamageSource& unk0, Actor& unk1) override;

    /**@vidx {23}*/
    virtual void teleportTo(const Vec3& unk0, bool shouldStopRiding, int unk, int unkn2, bool keepVelocity) override;

    /**@vidx {26}*/
    virtual void normalTick() override;

    /// @vidx {27}
    MC virtual void baseTick() override;

    /**@vidx {29}*/
    virtual bool startRiding(Actor& unk0) override;

    /**@vidx {30}*/
    virtual void addPassenger(Actor& unk0) override;

    /**@vidx {43}*/
    virtual bool isImmobile() const override;

    /**@vidx {45}*/
    virtual bool isSleeping() const override;

    /**@vidx {46}*/
    virtual void setSleeping(bool unk0) override;

    /**@vidx {48}*/
    virtual bool isBlocking() const override;

    /**@vidx {50}*/
    virtual bool isAlive() const override;

    /**@vidx {52}*/
    virtual bool isSurfaceMob() const override;

    /**@vidx {55}*/
    virtual void setTarget(Actor* unk0) override;

    /**@vidx {57}*/
    virtual bool attack(Actor& unk0, const ActorDamageCause& unk1) override;

    /**@vidx {64}*/
    virtual bool canPowerJump() const override;

    /**@vidx {70}*/
    virtual ActorDamageCause getBlockDamageCause(const Block& unk0) const override;

    /**@vidx {71}*/
    virtual bool doFireHurt(int unk0) override;

    /**@vidx {74}*/
    virtual void handleEntityEvent(ActorEvent unk0, int unk1) override;

    /**@vidx {78}*/
    virtual ArmorMaterialType getArmorMaterialTypeInSlot(ArmorSlot unk0) const override;

    /**@vidx {79}*/
    virtual int getArmorTextureIndexInSlot(ArmorSlot unk0) const override;

    /**@vidx {80}*/
    virtual float getArmorColorInSlot(ArmorSlot unk0, int unk1) const override;

    /**@vidx {81}*/
    virtual void setEquippedSlot(Puv::Legacy::EquipmentSlot unk0, const ItemStack& unk1) override;

    /**@vidx {91}*/
    virtual bool canFreeze() const override;

    /**@vidx {94}*/
    virtual bool canChangeDimensionsUsingPortal() const override;

    /**@vidx {98}*/
    virtual float causeFallDamageToActor(float unk0, float unk1, ActorDamageSource unk2) override;

    /**@vidx {102}*/
    virtual bool canBePulledIntoVehicle() const override;

    /**@vidx {103}*/
    virtual bool inCaravan() const override;

    /**@vidx {108}*/
    virtual void buildDebugInfo(std::string& unk0) const override;

    /**@vidx {110}*/
    virtual int getDeathTime() const override;

    /**@vidx {117}*/
    virtual void swing() override;

    /**@vidx {130}*/
    virtual void kill() override;

    /**@vidx {131}*/
    virtual void die(const ActorDamageSource& unk0) override;

    /**@vidx {132}*/
    virtual bool shouldDropDeathLoot() const override;

    /**@vidx {144}*/
    virtual void updateEntitySpecificMolangVariables(RenderParams& unk0) override;

    /**@vidx {146}*/
    virtual bool _hurt(const ActorDamageSource& unk0, float unk1, bool unk2, bool unk3) override;

    /**@vidx {147}*/
    virtual void readAdditionalSaveData(const CompoundTag& unk0, DataLoadHelper& unk1) override;

    /**@vidx {148}*/
    virtual void addAdditionalSaveData(CompoundTag& unk0) const override;

    /**@vidx {149}*/
    virtual void _playStepSound(const BlockPos& unk0, const Block& unk1) override;

    /**@vidx {151}*/
    virtual void knockback(Actor* unk0, int unk1, float unk2, float unk3, float unk4, float unk5, float unk6);

    /**@vidx {152}*/
    virtual void _unknown_152();

    /**@vidx {153}*/
    virtual void setSprinting(bool unk0);

    /**@vidx {154}*/
    virtual Puv::Legacy::LevelSoundEvent getDeathSound();

    /**@vidx {155}*/
    virtual float getSpeed() const;

    /**@vidx {156}*/
    virtual void setSpeed(float unk0);

    /**@vidx {157}*/
    virtual void hurtEffects(const ActorDamageSource& unk0, float unk1, bool unk2, bool unk3);

    /**@vidx {158}*/
    virtual void aiStep();

    /**@vidx {159}*/
    virtual void pushActors();

    /**@vidx {160}*/
    virtual bool checkSpawnRules(bool unk0);

    /**@vidx {161}*/
    virtual bool checkSpawnObstruction() const;

    /**@vidx {162}*/
    virtual int getItemUseDuration() const;

    /**@vidx {163}*/
    virtual float getItemUseStartupProgress() const;

    /**@vidx {164}*/
    virtual float getItemUseIntervalProgress() const;

    /**@vidx {165}*/
    virtual float getMaxHeadXRot();

    /**@vidx {166}*/
    virtual bool isAlliedTo(Mob* unk0);

    /**@vidx {167}*/
    virtual bool doHurtTarget(Actor* unk0, const ActorDamageCause& unk1);

    /**@vidx {168}*/
    virtual int getArmorValue() const;

    /**@vidx {169}*/
    virtual void hurtArmorSlots(const ActorDamageSource& unk0, int unk1, std::bitset<4> unk2);

    /**@vidx {170}*/
    virtual void setDamagedArmor(ArmorSlot unk0, const ItemStack& unk1);

    /**@vidx {171}*/
    virtual void _unknown_171();

    /**@vidx {172}*/
    virtual void sendArmor(std::bitset<4> unk0);

    /**@vidx {173}*/
    virtual std::vector<const ItemStack*> getAllHand() const;

    /**@vidx {174}*/
    virtual std::vector<const ItemStack*> getAllEquipment() const;

    /**@vidx {175}*/
    virtual void dropEquipmentOnDeath();

    /**@vidx {176}*/
    virtual void dropEquipmentOnDeath(const ActorDamageSource& unk0);

    /**@vidx {177}*/
    virtual void clearVanishEnchantedItemsOnDeath();

    /**@vidx {178}*/
    virtual void sendInventory(bool unk0);

    /**@vidx {179}*/
    virtual float getDamageAfterEnchantReduction(const ActorDamageSource& unk0, float unk1) const;

    /**@vidx {180}*/
    virtual bool createAIGoals();

    /**@vidx {181}*/
    virtual void _unknown_181();

    /**@vidx {182}*/
    virtual bool setItemSlot(Puv::Legacy::EquipmentSlot unk0, const ItemStack& unk1);

    /**@vidx {183}*/
    virtual void setTransitioningSitting(bool unk0);

    /**@vidx {184}*/
    virtual float _getWalkTargetValue(const BlockPos& unk0);

    /**@vidx {185}*/
    virtual bool canExistWhenDisallowMob() const;

    /**@vidx {186}*/
    virtual std::unique_ptr<BodyControl> initBodyControl();

    /**@vidx {187}*/
    virtual void newServerAiStep();

    /**@vidx {188}*/
    virtual void tickDeath();

    /**@vidx {189}*/
    virtual AABB _getAdjustedAABBForSpawnCheck(const AABB& unk0, const Vec3& unk1) const;

    // non-virtuals
    int getCurrentSwingDuration() const;
};
#pragma pack(pop)

// 1.21.0.3
//static_assert(sizeof(Mob) == 1512);