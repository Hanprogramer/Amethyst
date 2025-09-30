/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

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
#include <mc/src/common/world/item/ItemCommandVisibility.hpp>

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

    std::string mTextureAtlasFile;
    int mFrameCount;
    bool mAnimatesInToolbar;
    bool mIsMirroredArt;
    UseAnim mUseAnim;
    std::string mHoverTextColorFormat;
    int mIconFrame;
    int mAtlasFrame;
    int mAtlasTotalFrames;
    std::string mIconName;
    std::string mAtlasName;
    uint8_t mMaxStackSize;
    short mId;
    std::string mDescriptionId;
    HashedString mRawNameId;
    std::string mNamespace;
    HashedString mFullName;
    short mMaxDamage;
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
    WeakPtr<BlockLegacy> mLegacyBlock;
    CreativeItemCategory mCreativeCategory;
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

public:
    /// @vidx {0}
	MC virtual ~Item();

	/// @vidx {1}
	MC virtual bool initServer(const Json::Value& config, const SemVersion& version, bool unk2, const Experiments& experiments);

	/// @vidx {2}
	MC virtual void tearDown();

	/// @vidx {3}
	MC virtual Item& setDescriptionId(const std::string& descriptionId);

	/// @vidx {4}
	MC virtual const std::string& getDescriptionId() const;

	/// @vidx {5}
	MC virtual int getMaxUseDuration(const ItemStack* item) const;

	/// @vidx {6}
	MC virtual bool isMusicDisk() const;

	/// @vidx {7}
	MC virtual void executeEvent(ItemStackBase& stack, const std::string& eventName, RenderParams& renderParams) const;

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
	MC virtual ItemComponent* getComponent(const HashedString& componentName) const;

	/// @vidx {23}
	MC virtual IFoodItemComponent* getFood() const;

	/// @vidx {24}
	MC virtual Item& setMaxDamage(int maxDamage);

	/// @vidx {25}
	MC virtual Item& setMaxUseDuration(int duration);

	/// @vidx {26}
	MC virtual std::unique_ptr<CompoundTag> buildNetworkTag() const;

	/// @vidx {27}
	MC virtual void initializeFromNetwork(const CompoundTag& userData);

	/// @vidx {28}
	MC virtual std::vector<std::string> validateFromNetwork(const CompoundTag& userData);

	/// @vidx {29}
	MC virtual BlockShape getBlockShape() const;

	/// @vidx {30}
	MC virtual bool canBeDepleted() const;

	/// @vidx {31}
	MC virtual bool canDestroySpecial(const Block& block) const;

	/// @vidx {32}
	MC virtual int getLevelDataForAuxValue(int auxValue) const;

	/// @vidx {33}
	MC virtual bool isStackedByData() const;

	/// @vidx {34}
	MC virtual short getMaxDamage() const;

	/// @vidx {35}
	MC virtual int getAttackDamage() const;

	/// @vidx {36}
	MC virtual float getAttackDamageBonus(const Actor& actor, float unk1) const;

	/// @vidx {37}
	MC virtual bool isHandEquipped() const;

	/// @vidx {38}
	MC virtual bool isGlint(const ItemStackBase& stack) const;

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
	MC virtual bool shouldInteractionWithBlockBypassLiquid(const Block& block) const;

	/// @vidx {47}
	MC virtual bool requiresInteract() const;

	/// @vidx {48}
	MC virtual void appendFormattedHovertext(const ItemStackBase& stack, Level& level, std::string& outText, bool unk3) const;

	/// @vidx {49}
	MC virtual bool isValidRepairItem(const ItemStackBase& targetStack, const ItemStackBase& repairStack, const BaseGameVersion& version) const;

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
	MC virtual bool isValidAuxValue(int auxValue) const;

	/// @vidx {57}
	MC virtual int getDamageChance(int unk0) const;

	/// @vidx {58}
	MC virtual float getViewDamping() const;

	/// @vidx {59}
	MC virtual bool uniqueAuxValues() const;

	/// @vidx {60}
	MC virtual bool isActorPlacerItem() const;

	/// @vidx {61}
	MC virtual bool isMultiColorTinted(const ItemStack& stack) const;

	/// @vidx {62}
	MC virtual mce::Color getColor(const CompoundTag* unk0, const ItemDescriptor& descriptor) const;

	/// @vidx {64}
	MC virtual bool hasCustomColor(const ItemStackBase& stack) const;

	/// @vidx {63}
	MC virtual bool hasCustomColor(const CompoundTag* unk0) const;

	/// @vidx {65}
	MC virtual void clearColor(ItemStackBase& stack) const;

	/// @vidx {66}
	MC virtual void setColor(ItemStackBase& stack, const mce::Color& color) const;

	/// @vidx {67}
	MC virtual mce::Color getBaseColor(const ItemStack& stack) const;

	/// @vidx {68}
	MC virtual mce::Color getSecondaryColor(const ItemStack& stack) const;

	/// @vidx {69}
	MC virtual ActorDefinitionIdentifier getActorIdentifier(const ItemStack& stack) const;

	/// @vidx {70}
	MC virtual int buildIdAux(short unk0, const CompoundTag* unk1) const;

	/// @vidx {71}
	MC virtual bool canUseOnSimTick() const;

	/// @vidx {72}
	MC virtual ItemStack& use(ItemStack& stack, Player& player) const;

	/// @vidx {73}
	MC virtual Actor* createProjectileActor(BlockSource& source, const ItemStack& stack, const Vec3& pos, const Vec3& velocity) const;

	/// @vidx {74}
	MC virtual bool dispense(BlockSource& source, Container& container, int slot, const Vec3& pos, FacingID facing) const;

	/// @vidx {75}
	MC virtual ItemUseMethod useTimeDepleted(ItemStack& stack, Level* level, Player* player) const;

	/// @vidx {76}
	MC virtual void releaseUsing(ItemStack& stack, Player* player, int duration) const;

	/// @vidx {77}
	MC virtual float getDestroySpeed(const ItemStackBase& stack, const Block& block) const;

	/// @vidx {78}
	MC virtual void hurtActor(ItemStack& stack, Actor& actor, Mob& mob) const;

	/// @vidx {79}
	MC virtual void hitActor(ItemStack& stack, Actor& actor, Mob& mob) const;

	/// @vidx {80}
	MC virtual void hitBlock(ItemStack& stack, const Block& block, const BlockPos& pos, Mob& mob) const;

	/// @vidx {81}
	MC virtual bool mineBlock(ItemStack& stack, const Block& block, int unk2, int unk3, int unk4, Actor* actor) const;

	/// @vidx {82}
	MC virtual std::string buildDescriptionName(const ItemStackBase& stack) const;

	/// @vidx {83}
	MC virtual std::string buildDescriptionId(const ItemDescriptor& descriptor, const CompoundTag* tag) const;

	/// @vidx {84}
	MC virtual std::string buildEffectDescriptionName(const ItemStackBase& stack) const;

	/// @vidx {85}
	MC virtual void readUserData(ItemStackBase& stack, IDataInput& input, ReadOnlyBinaryStream& stream) const;

	/// @vidx {86}
	MC virtual void writeUserData(const ItemStackBase& stack, IDataOutput& output) const;

	/// @vidx {87}
	MC virtual FacingID getMaxStackSize(const ItemDescriptor& descriptor) const;

	/// @vidx {88}
	MC virtual bool inventoryTick(ItemStack& stack, Level& level, Actor& actor, int unk3, bool unk4) const;

	/// @vidx {89}
	MC virtual void refreshedInContainer(const ItemStackBase& stack, Level& level) const;

	/// @vidx {90}
	MC virtual const HashedString& getCooldownType() const;

	/// @vidx {91}
	MC virtual int getCooldownTime() const;

	/// @vidx {93}
	MC virtual void fixupCommon(ItemStackBase& stack) const;

	/// @vidx {92}
	MC virtual void fixupCommon(ItemStackBase& stack, Level& level) const;

	/// @vidx {94}
	MC virtual InHandUpdateType getInHandUpdateType(const Player& player, const ItemStack& currentStack, const ItemStack& prevStack, bool unk3, bool unk4) const;

	/// @vidx {95}
	MC virtual bool validFishInteraction(int unk0) const;

	/// @vidx {96}
	MC virtual void enchantProjectile(const ItemStackBase& stack, Actor& actor) const;

	/// @vidx {97}
	MC virtual ActorLocation getEquipLocation() const;

	/// @vidx {98}
	MC virtual Puv::Legacy::LevelSoundEvent getEquipSound() const;

	/// @vidx {99}
	MC virtual bool shouldSendInteractionGameEvents() const;

	/// @vidx {100}
	MC virtual bool useInterruptedByAttacking() const;

	/// @vidx {101}
	MC virtual bool hasSameRelevantUserData(const ItemStackBase& stack, const ItemStackBase& prevStack) const;

	/// @vidx {102}
	MC virtual void initClient(const Json::Value& config, const SemVersion& version, bool unk2, const Experiments& experiments);

	/// @vidx {103}
	MC virtual Item& setIconInfo(const std::string& iconName, int iconFrame);

	/// @vidx {104}
	MC virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase& stack, int unk1, bool unk2) const;

	/// @vidx {105}
	MC virtual std::string getInteractText(const Player& player) const;

	/// @vidx {106}
	MC virtual int getAnimationFrameFor(Mob* mob, bool unk1, const ItemStack* stack, bool unk3) const;

	/// @vidx {107}
	MC virtual bool isEmissive(int unk0) const;

	/// @vidx {108}
	MC virtual Brightness getLightEmission(int unk0) const;

	/// @vidx {109}
	MC virtual int getIconYOffset() const;

	/// @vidx {110}
	MC virtual bool canBeCharged() const;

	/// @vidx {111}
	MC virtual void playSoundIncrementally(const ItemStack& stack, Mob& mob) const;

	/// @vidx {112}
	MC virtual float getFurnaceXPmultiplier(const ItemStackBase& stack) const;

	/// @vidx {113}
	MC virtual std::string getAuxValuesDescription() const;

	/// @vidx {114}
	MC virtual bool calculatePlacePos(ItemStackBase& stack, Actor& actor, FacingID& face, BlockPos& pos) const;

	/// @vidx {115}
	MC virtual bool _checkUseOnPermissions(Actor& actor, ItemStackBase& stack, const FacingID& face, const BlockPos& pos) const;

	/// @vidx {116}
	MC virtual bool _calculatePlacePos(ItemStackBase& stack, Actor& actor, FacingID& face, BlockPos& pos) const;

	/// @vidx {117}
	MC virtual bool _shouldAutoCalculatePlacePos() const;

	/// @vidx {118}
	MC virtual InteractionResult _useOn(ItemStack& stack, Actor& actor, BlockPos pos, FacingID face, const Vec3& hit) const;

public:
	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 0F B7 D8}
    MC Item(const std::string& identifier, short numId);

	// UnknownReturn getBaseRarity() const;

	// ICameraItemComponent* getCamera() const;

	// std::vector<CommandName> getCommandNames() const;

	CreativeItemCategory getCreativeCategory() const;

	const std::string& getCreativeGroup() const;

	short getDamageValue(const CompoundTag* userData) const;

	int getFrameCount() const;

	const std::string& getFullItemName() const;

	const HashedString& getFullNameHash() const;

	float getFurnaceBurnIntervalMultipler() const;

	std::string getHoverTextColor(const ItemStackBase& stack) const;

	short getId() const;

	const WeakPtr<const BlockLegacy>& getLegacyBlock() const;

	// UnknownReturn getLegacyBlockForRendering() const;

	// int getMaxUseDuration(const ItemInstance* item) const;

	Interactions::Mining::MineBlockItemEffectType getMineBlockType() const;

	const std::string& getNamespace() const;

	// UnknownReturn getRarity(const ItemStackBase& stack) const;

	const HashedString& getRawNameHash() const;

	const std::string& getRawNameId() const;

	// UnknownReturn getRendererId() const;

	const BaseGameVersion& getRequiredBaseGameVersion() const;

	// UnknownReturn getSeed() const;

	// std::string getSerializedName() const;

	UseAnim getUseAnimation() const;
	
	void setDamageValue(ItemStackBase& stack, short value) const;
	
	Item& setAllowOffhand(bool allowOffhand);
	
	Item& setCategory(CreativeItemCategory category);

	Item& setCreativeGroup(const std::string& group);

	Item& setExplodable(bool isExplodable);

	Item& setFireResistant(bool isFireResistant);

	Item& setFurnaceBurnIntervalMultiplier(float multiplier);

	Item& setFurnaceXPmultiplier(float multiplier);

	Item& setHandEquipped();

	Item& setHoverTextColorFormat(std::string_view format);

	Item& setIsGlint(bool isGlint);

	Item& setIsHiddenInCommands(ItemCommandVisibility visibility);

	Item& setIsMirroredArt(bool isMirroredArt);

	Item& setMaxStackSize(uint8_t maxStackSize);

	Item& setMinRequiredBaseGameVersion(const BaseGameVersion& version);

	Item& setRequiresWorldBuilder(bool requiresWorldBuilder);

	Item& setShouldDespawn(bool shouldDespawn);

	Item& setStackedByData(bool stackedByData);

	Item& addTag(const ItemTag& tag);

	Item& addTag(const HashedString& tag);

	Item& addTags(std::initializer_list<std::reference_wrapper<const ItemTag>> tags);

	Item& setUseAnimation(UseAnim useAnim);

	// void removeDamageValue(ItemStackBase& stack) const;

	// bool canBeUsedInCommands(const BaseGameVersion& unk0) const;

	// bool canUseSeed(Actor& actor, BlockPos at, FacingID unk2) const;

	// bool hasDamageValue(const CompoundTag* unk0) const;

	bool hasTag(const ItemTag& unk0) const;

	bool hasTag(const HashedString& unk0) const;

	bool isAnimatedInToolbar() const;

	bool isCamera() const;

	// bool isCommandOnly(const BaseGameVersion& unk0) const;

	// bool isElytra() const;

	// UnknownReturn isElytra(const ItemDescriptor& unk0);

	// static bool isElytraBroken(int unk0);

	bool isExplodable() const;

	bool isFireResistant() const;

	// static bool isFlyEnabled(const ItemInstance& unk0);

	bool isMirroredArt() const;

	// bool isNameTag() const;

	// static bool isSameTypeAndItem(const ItemStackBase& stack, const ItemStackBase& stack);

	bool isSeed() const;

	bool shouldDespawn() const;

	// std::string buildCategoryDescriptionName() const;

	// ItemDescriptor buildDescriptor(short unk0, const CompoundTag* unk1) const;

	// UnknownReturn buildRedactedDescriptionName(const ItemStackBase& stack) const;

	// bool _dispenseHoneycombItem(BlockSource& unk0, Container& unk1, int unk2, const Vec3& unk3) const;

	// UnknownReturn _getUpgradedRarityForEnchantedItem(Rarity unk0);

	// void _helpChangeInventoryItemInPlace(Actor& actor, ItemStack& unk1, ItemStack& unk2, ItemAcquisitionMethod unk3) const;

	// CoordinatorResult _sendTryPlaceBlockEvent(const Block& unk0, const BlockSource& unk1, const Actor& actor, const BlockPos& at, FacingID unk4, const Vec3& unk5) const;

	// UnknownReturn _textMatch(const std::string& unk0, const std::string& unk1, bool unk2);

	// UnknownReturn _tryCorrectAnyAuxValue(ItemStackBase& stack) const;

	bool allowOffhand() const;

	void clearTags();

	// float destroySpeedBonus(const ItemStackBase& stack) const;

	// UnknownReturn executeOnResetBAIcallbacks() const;

	// void fixupOnLoad(ItemStackBase& stack) const;

	// void fixupOnLoad(ItemStackBase& stack, Level& unk1) const;

	// UnknownReturn ignoresPermissions() const;

	// UnknownReturn initClient(const Json::Value& unk0, const SemVersion& unk1, JsonBetaState unk2, IPackLoadContext& unk3);

	// UnknownReturn initServer(const Json::Value& unk0, const SemVersion& unk1, IPackLoadContext& unk2, JsonBetaState unk3);

	// bool operator==(const Item& unk0) const;

	// UnknownReturn operator(const Item& unk0) const;

	// UnknownReturn reloadIcon();

	// UnknownReturn resetId(short unk0);

	// static NewBlockID toBlockId(short unk0);

	// bool updateCustomBlockEntityTag(BlockSource& unk0, ItemStackBase& stack, const BlockPos& at) const;

	// void useOn(ItemStack& unk0, Actor& actor, int unk2, int unk3, int unk4, FacingID unk5, const Vec3& unk6, ItemUsedOnEventContext unk7) const;

    /// @signature {48 89 4C 24 ? 53 48 81 EC ? ? ? ? 48 8B D9 45 33 C9}
    MC static void addCreativeItem(ItemRegistryRef*, const Block*);
};

// 1.21.0.3
//static_assert(sizeof(Item) == 600);