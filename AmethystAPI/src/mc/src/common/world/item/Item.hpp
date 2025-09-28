/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <memory>
#include <string>
#include <vector>

#include <mc/src-deps/core/math/Color.hpp>
#include <mc/src/common/SharedPtr.hpp>
#include <mc/src/common/nbt/CompoundTag.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/level/block/BlockLegacy.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/block/BlockShape.hpp>
#include <mc/src/common/world/item/ResolvedItemIconInfo.hpp>
#include <mc/src/common/world/item/UseAnim.hpp>
#include <mc/src-deps/shared_types/legacy/LevelSoundEvent.hpp>

// Auto-generated: Unknown complete types
enum ItemColor {};
struct ActorDefinitionIdentifier;
enum ItemUseMethod {};
enum InHandUpdateType {};
enum ActorLocation {};

class InteractionResult {
public:
    enum class Result : int32_t {
        SUCCESS = 1,
        SWING = 2,
    };

public:
    int mResult;

    InteractionResult() = default;
    InteractionResult(const InteractionResult&) = default;
    InteractionResult& operator=(const InteractionResult&) = default;
};

// Auto-generated: Forward declarations
namespace Json {
class Value;
}
class SemVersion;
class Experiments;
class Item;
class ItemStack;
class ItemStackBase;
class RenderParams;
class ItemComponent;
class HashedString;
class IFoodItemComponent;
class Block;
class Level;
class BaseGameVersion;
class ItemDescriptor;
class Player;
class BlockSource;
class Container;
class Vec3;
class Actor;
class Mob;
class IDataInput;
class ReadOnlyBinaryStream;
class IDataOutput;
class FoodItemComponentLegacy {};
class SeedItemComponentLegacy {};
class CameraItemComponentLegacy {};

namespace Interactions::Mining {
    enum MineBlockItemEffectType : int32_t {};
}

class ItemTag : public HashedString {

};

/// @vptr {0x4DFCE10}
class Item {
public:
    MC static uintptr_t $vtable_for_this;

    /* this + 8   */ std::string mTextureAtlasFile;
    /* this + 40  */ int mFrameCount;
    /* this + 44  */ bool mAnimatesInToolbar;
    /* this + 45  */ bool mIsMirroredArt;
    /* this + 46  */ UseAnim mUseAnim;
    /* this + 64  */ std::string mHoverTextColorFormat;

    int mIconFrame;
    int mAtlasFrame;
    int mAtlasTotalFrames;
    std::string mIconName;
    std::string mAtlasName;
    uint8_t mMaxStackSize;

    /* this + 162 */ short mId;
    /* this + 168 */ std::string mDescriptionId;
    /* this + 200 */ HashedString mRawNameId;
    /* this + 248 */ std::string mNamespace;
    /* this + 280 */ HashedString mFullName;
    /* this + 328 */ short mMaxDamage;

    bool mIsGlint : 1;
    bool mHandEquipped : 1;
    bool mIsStackedByData : 1;
    bool mRequiresWorldBuilder : 1;
    bool mExplodable : 1;
    bool mFireResistant : 1;
    bool mShouldDespawn : 1;
    bool mAllowOffhand : 1;
    bool mIgnoresPermissions : 1;

    int mMaxUseDuration;
    BaseGameVersion mMinRequiredBaseGameVersion;

    /* this + 456 */ WeakPtr<BlockLegacy> mLegacyBlock;
    /* this + 464 */ CreativeItemCategory mCreativeCategory;

    Item* mCraftingRemainingItem;
    std::string mCreativeGroup;
    float mFurnaceBurnIntervalModifier;
    float mFurnaceXPmultiplier;
    bool mIsHiddenInCommands;

    Interactions::Mining::MineBlockItemEffectType mMineBlockType;
    std::unique_ptr<FoodItemComponentLegacy> mFoodComponentLegacy;
    std::unique_ptr<SeedItemComponentLegacy> mSeedComponent;
    std::unique_ptr<CameraItemComponentLegacy> mCameraComponentLegacy;
    std::vector<std::function<void __cdecl(void)>> mOnResetBAIcallbacks;
    std::vector<ItemTag> mTags;
    std::byte padding596[4]; // idk why the size is 600 not 596

public:
    /// @vidx {0}
	MC virtual ~Item();

	/// @vidx {1}
	MC virtual bool initServer(const Json::Value& unk0, const SemVersion& unk1, bool unk2, const Experiments& unk3);

	/// @vidx {2}
	MC virtual void tearDown();

	/// @vidx {3}
	MC virtual Item& setDescriptionId(const std::string& unk0);

	/// @vidx {4}
	MC virtual const std::string& getDescriptionId() const;

	/// @vidx {5}
	MC virtual int getMaxUseDuration(const ItemStack* unk0) const;

	/// @vidx {6}
	MC virtual bool isMusicDisk() const;

	/// @vidx {7}
	MC virtual void executeEvent(ItemStackBase& unk0, const std::string& unk1, RenderParams& unk2) const;

	/// @vidx {8}
	MC virtual bool isComponentBased() const;

	/// @vidx {9}
	MC virtual bool isHumanoidArmor() const;

	/// @vidx {10}
	MC virtual bool isBlockPlanterItem() const;

	/// @vidx {11}
	MC virtual bool isBucket() const;

	/// @vidx {12}
	MC virtual bool isCandle() const;

	/// @vidx {13}
	MC virtual bool isDamageable() const;

	/// @vidx {14}
	MC virtual bool isDyeable() const;

	/// @vidx {15}
	MC virtual bool isDye() const;

	/// @vidx {16}
	MC virtual ItemColor getItemColor() const;

	/// @vidx {17}
	MC virtual bool isFertilizer() const;

	/// @vidx {18}
	MC virtual bool isFood() const;

	/// @vidx {19}
	MC virtual bool isThrowable() const;

	/// @vidx {20}
	MC virtual bool isUseable() const;

	/// @vidx {21}
	MC virtual bool isTrimAllowed() const;

	/// @vidx {22}
	MC virtual ItemComponent* getComponent(const HashedString& unk0) const;

	/// @vidx {23}
	MC virtual IFoodItemComponent* getFood() const;

	/// @vidx {24}
	MC virtual Item& setMaxDamage(int unk0);

	/// @vidx {25}
	MC virtual Item& setMaxUseDuration(int unk0);

	/// @vidx {26}
	MC virtual std::unique_ptr<CompoundTag> buildNetworkTag() const;

	/// @vidx {27}
	MC virtual void initializeFromNetwork(const CompoundTag& unk0);

	/// @vidx {28}
	MC virtual std::vector<std::string> validateFromNetwork(const CompoundTag& unk0);

	/// @vidx {29}
	MC virtual BlockShape getBlockShape() const;

	/// @vidx {30}
	MC virtual bool canBeDepleted() const;

	/// @vidx {31}
	MC virtual bool canDestroySpecial(const Block& unk0) const;

	/// @vidx {32}
	MC virtual int getLevelDataForAuxValue(int unk0) const;

	/// @vidx {33}
	MC virtual bool isStackedByData() const;

	/// @vidx {34}
	MC virtual short getMaxDamage() const;

	/// @vidx {35}
	MC virtual int getAttackDamage() const;

	/// @vidx {36}
	MC virtual float getAttackDamageBonus(const Actor& unk0, float unk1) const;

	/// @vidx {37}
	MC virtual bool isHandEquipped() const;

	/// @vidx {38}
	MC virtual bool isGlint(const ItemStackBase& unk0) const;

	/// @vidx {39}
	MC virtual bool isPattern() const;

	/// @vidx {40}
	MC virtual int getPatternIndex() const;

	/// @vidx {41}
	MC virtual bool showsDurabilityInCreative() const;

	/// @vidx {42}
	MC virtual bool isWearableThroughLootTable(const CompoundTag* unk0) const;

	/// @vidx {43}
	MC virtual bool canDestroyInCreative() const;

	/// @vidx {44}
	MC virtual bool isDestructive(int unk0) const;

	/// @vidx {45}
	MC virtual bool isLiquidClipItem() const;

	/// @vidx {46}
	MC virtual bool shouldInteractionWithBlockBypassLiquid(const Block& unk0) const;

	/// @vidx {47}
	MC virtual bool requiresInteract() const;

	/// @vidx {48}
	MC virtual void appendFormattedHovertext(const ItemStackBase& unk0, Level& unk1, std::string& unk2, bool unk3) const;

	/// @vidx {49}
	MC virtual bool isValidRepairItem(const ItemStackBase& unk0, const ItemStackBase& unk1, const BaseGameVersion& unk2) const;

	/// @vidx {50}
	MC virtual int getEnchantSlot() const;

	/// @vidx {51}
	MC virtual int getEnchantValue() const;

	/// @vidx {52}
	MC virtual int getArmorValue() const;

	/// @vidx {53}
	MC virtual int getToughnessValue() const;

	/// @vidx {54}
	MC virtual Puv::Legacy::LevelSoundEvent getBreakSound() const;

	/// @vidx {55}
	MC virtual bool isComplex() const;

	/// @vidx {56}
	MC virtual bool isValidAuxValue(int unk0) const;

	/// @vidx {57}
	MC virtual int getDamageChance(int unk0) const;

	/// @vidx {58}
	MC virtual float getViewDamping() const;

	/// @vidx {59}
	MC virtual bool uniqueAuxValues() const;

	/// @vidx {60}
	MC virtual bool isActorPlacerItem() const;

	/// @vidx {61}
	MC virtual bool isMultiColorTinted(const ItemStack& unk0) const;

	/// @vidx {62}
	MC virtual mce::Color getColor(const CompoundTag* unk0, const ItemDescriptor& unk1) const;

	/// @vidx {63}
	MC virtual bool hasCustomColor(const ItemStackBase& unk0) const;

	/// @vidx {64}
	MC virtual bool hasCustomColor(const CompoundTag* unk0) const;

	/// @vidx {65}
	MC virtual void clearColor(ItemStackBase& unk0) const;

	/// @vidx {66}
	MC virtual void setColor(ItemStackBase& unk0, const mce::Color& unk1) const;

	/// @vidx {67}
	MC virtual mce::Color getBaseColor(const ItemStack& unk0) const;

	/// @vidx {68}
	MC virtual mce::Color getSecondaryColor(const ItemStack& unk0) const;

	/// @vidx {69}
	MC virtual ActorDefinitionIdentifier getActorIdentifier(const ItemStack& unk0) const;

	/// @vidx {70}
	MC virtual int buildIdAux(short unk0, const CompoundTag* unk1) const;

	/// @vidx {71}
	MC virtual bool canUseOnSimTick() const;

	/// @vidx {72}
	MC virtual ItemStack& use(ItemStack& unk0, Player& unk1) const;

	/// @vidx {73}
	MC virtual Actor* createProjectileActor(BlockSource& unk0, const ItemStack& unk1, const Vec3& unk2, const Vec3& unk3) const;

	/// @vidx {74}
	MC virtual bool dispense(BlockSource& unk0, Container& unk1, int unk2, const Vec3& unk3, FacingID unk4) const;

	/// @vidx {75}
	MC virtual ItemUseMethod useTimeDepleted(ItemStack& unk0, Level* unk1, Player* unk2) const;

	/// @vidx {76}
	MC virtual void releaseUsing(ItemStack& unk0, Player* unk1, int unk2) const;

	/// @vidx {77}
	MC virtual float getDestroySpeed(const ItemStackBase& unk0, const Block& unk1) const;

	/// @vidx {78}
	MC virtual void hurtActor(ItemStack& unk0, Actor& unk1, Mob& unk2) const;

	/// @vidx {79}
	MC virtual void hitActor(ItemStack& unk0, Actor& unk1, Mob& unk2) const;

	/// @vidx {80}
	MC virtual void hitBlock(ItemStack& unk0, const Block& unk1, const BlockPos& unk2, Mob& unk3) const;

	/// @vidx {81}
	MC virtual bool mineBlock(ItemStack& unk0, const Block& unk1, int unk2, int unk3, int unk4, Actor* unk5) const;

	/// @vidx {82}
	MC virtual std::string buildDescriptionName(const ItemStackBase& unk0) const;

	/// @vidx {83}
	MC virtual std::string buildDescriptionId(const ItemDescriptor& unk0, const CompoundTag* unk1) const;

	/// @vidx {84}
	MC virtual std::string buildEffectDescriptionName(const ItemStackBase& unk0) const;

	/// @vidx {85}
	MC virtual void readUserData(ItemStackBase& unk0, IDataInput& unk1, ReadOnlyBinaryStream& unk2) const;

	/// @vidx {86}
	MC virtual void writeUserData(const ItemStackBase& unk0, IDataOutput& unk1) const;

	/// @vidx {87}
	MC virtual FacingID getMaxStackSize(const ItemDescriptor& unk0) const;

	/// @vidx {88}
	MC virtual bool inventoryTick(ItemStack& unk0, Level& unk1, Actor& unk2, int unk3, bool unk4) const;

	/// @vidx {89}
	MC virtual void refreshedInContainer(const ItemStackBase& unk0, Level& unk1) const;

	/// @vidx {90}
	MC virtual const HashedString& getCooldownType() const;

	/// @vidx {91}
	MC virtual int getCooldownTime() const;

	/// @vidx {92}
	MC virtual void fixupCommon(ItemStackBase& unk0) const;

	/// @vidx {93}
	MC virtual void fixupCommon(ItemStackBase& unk0, Level& unk1) const;

	/// @vidx {94}
	MC virtual InHandUpdateType getInHandUpdateType(const Player& unk0, const ItemStack& unk1, const ItemStack& unk2, bool unk3, bool unk4) const;

	/// @vidx {95}
	MC virtual bool validFishInteraction(int unk0) const;

	/// @vidx {96}
	MC virtual void enchantProjectile(const ItemStackBase& unk0, Actor& unk1) const;

	/// @vidx {97}
	MC virtual ActorLocation getEquipLocation() const;

	/// @vidx {98}
	MC virtual Puv::Legacy::LevelSoundEvent getEquipSound() const;

	/// @vidx {99}
	MC virtual bool shouldSendInteractionGameEvents() const;

	/// @vidx {100}
	MC virtual bool useInterruptedByAttacking() const;

	/// @vidx {101}
	MC virtual bool hasSameRelevantUserData(const ItemStackBase& unk0, const ItemStackBase& unk1) const;

	/// @vidx {102}
	MC virtual void initClient(const Json::Value& unk0, const SemVersion& unk1, bool unk2, const Experiments& unk3);

	/// @vidx {103}
	MC virtual Item& setIconInfo(const std::string& unk0, int unk1);

	/// @vidx {104}
	MC virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase& unk0, int unk1, bool unk2) const;

	/// @vidx {105}
	MC virtual std::string getInteractText(const Player& unk0) const;

	/// @vidx {106}
	MC virtual int getAnimationFrameFor(Mob* unk0, bool unk1, const ItemStack* unk2, bool unk3) const;

	/// @vidx {107}
	MC virtual bool isEmissive(int unk0) const;

	/// @vidx {108}
	MC virtual Brightness getLightEmission(int unk0) const;

	/// @vidx {109}
	MC virtual int getIconYOffset() const;

	/// @vidx {110}
	MC virtual bool canBeCharged() const;

	/// @vidx {111}
	MC virtual void playSoundIncrementally(const ItemStack& unk0, Mob& unk1) const;

	/// @vidx {112}
	MC virtual float getFurnaceXPmultiplier(const ItemStackBase& unk0) const;

	/// @vidx {113}
	MC virtual std::string getAuxValuesDescription() const;

	/// @vidx {114}
	MC virtual bool calculatePlacePos(ItemStackBase& unk0, Actor& unk1, FacingID& unk2, BlockPos& unk3) const;

	/// @vidx {115}
	MC virtual bool _checkUseOnPermissions(Actor& unk0, ItemStackBase& unk1, const FacingID& unk2, const BlockPos& unk3) const;

	/// @vidx {116}
	MC virtual bool _calculatePlacePos(ItemStackBase& unk0, Actor& unk1, FacingID& unk2, BlockPos& unk3) const;

	/// @vidx {117}
	MC virtual bool _shouldAutoCalculatePlacePos() const;

	/// @vidx {118}
	MC virtual InteractionResult _useOn(ItemStack& unk0, Actor& unk1, BlockPos unk2, FacingID unk3, const Vec3& unk4) const;

public:
	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 0F B7 D8}
    MC Item(const std::string&, short);

    short getDamageValue(CompoundTag* mUserData) const;
    const std::string& getRawNameId() const;
    void setAllowOffhand(bool allowsOffhand);

    /// @signature {48 89 4C 24 ? 53 48 81 EC ? ? ? ? 48 8B D9 45 33 C9}
    MC static void addCreativeItem(ItemRegistryRef*, const Block*);
    
    bool hasTag(const HashedString& tag) const;
    UseAnim getUseAnim() const;
};

// 1.21.0.3
//static_assert(sizeof(Item) == 600);