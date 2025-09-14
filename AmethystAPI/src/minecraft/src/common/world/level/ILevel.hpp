/// @symbolgeneration
#pragma once
#include <gsl/gsl>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <minecraft/src/common/gamerefs/WeakRef.hpp>
#include <minecraft/src-deps/core/file/Path.hpp>
#include <minecraft/src/common/world/level/ChunkPos.hpp>
#include <minecraft/src/common/world/level/Tick.hpp>
#include <minecraft/src/common/world/level/storage/StorageVersion.hpp>
#include <minecraft/src/common/world/level/block/LevelEvent.hpp>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>
#include <minecraft/src/common/world/phys/Vec3.hpp>
#include <minecraft/src-deps/shared_types/legacy/LevelSoundEvent.hpp>
#include <minecraft/src/common/world/level/GameType.hpp>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <minecraft/src-client/common/client/social/MultiplayerGameinfo.hpp>
#include <minecraft/src/common/world/Difficulty.hpp>
#include <minecraft/src-deps/core/threading/TaskGroup.hpp>
#include <amethyst/Imports.hpp>

// Auto-generated: Forward declarations
namespace PlayerCapabilities { struct ISharedController; }
namespace PositionTrackingDB { class PositionTrackingDBClient; }
namespace cg { class ImageBuffer; }
namespace mce {class UUID; class Color; }
class EntityContext;
struct ActorUniqueID;
class LevelSettings;
class LevelData;
class Experiments;
class ChunkTickRangeManager;
class PortalForcer;
class Player;
class Actor;
class Spawner;
class ProjectileFactory;
class ActorDefinitionGroup;
class BlockDefinitionGroup;
class PropertyGroupManager;
class AutomationBehaviorTreeGroup;
class BehaviorFactory;
class InternalComponentRegistry;
class BlockSource;
class LevelChunk;
class Mob;
class IMinecraftEventing;
class BiomeManager;
class LevelListener;
class ActorDamageSource;
class Explosion;
class BlockPos;
class NavigationComponent;
class PhotoStorage;
class TickingAreasManager;
struct ActorDefinitionIdentifier;
class IConstBlockSource;
class PlayerEventCoordinator;
class ServerPlayerEventCoordinator;
class ClientPlayerEventCoordinator;
class ActorEventCoordinator;
class BlockEventCoordinator;
class ItemEventCoordinator;
class ServerNetworkEventCoordinator;
class ScriptingEventCoordinator;
class ScriptDeferredEventCoordinator;
class LevelEventCoordinator;
class CompoundTag;
class UserEntityIdentifierComponent;
class Block;
struct Bounds;
class ChunkSource;
class NetworkIdentifier;
class _TickPtr;
class Particle;
class HashedString;
class MolangVariableMap;
struct ResolvedItemIconInfo;
class SavedDataStorage;
class MapItemSavedData;
class ActorInfoRegistry;
class EntitySystems;
class TagRegistry;
struct PlayerMovementSettings;
class SerializedSkin;
class PacketSender;
class HitResult;
struct AdventureSettings;
class GameRules;
class Abilities;
class PermissionsHandler;
struct ScreenshotOptions;
class LootTables;
class LayeredAbilities;
class Recipes;
class BlockReducer;
class ItemComponentPacket;
class BlockLegacy;
class Level;
class ChangeDimensionRequest;
class BossEventSubscriptionManager;
class ActorAnimationGroup;
class ActorAnimationControllerGroup;
class DimensionConversionData;
class StrictEntityContext;
class ActorRuntimeID;
class StructureManager;
class Path;
class PlayerSleepStatus;
class EducationLevelSettings;
class ActorEvent;
class IUnknownBlockTypeRegistry;
class NetEventCallback;
class LevelSoundManager;
class SoundPlayerInterface;
class BlockTypeRegistry;
class ChunkViewSource;
class WeakEntityRef;
class Dimension;
class TickingAreaList;
enum class ParticleType : int {};
class BlockPalette;

class ILevel : public Bedrock::EnableNonOwnerReferences {
public:
    /**@vIndex {0}*/
    MC virtual ~ILevel();

    /**@vIndex {1}*/
    MC virtual bool initialize(const std::string&, const LevelSettings&, LevelData*, const Experiments&, const std::string*);

    /**@vIndex {2}*/
    MC virtual void startLeaveGame();

    /**@vIndex {3}*/
    MC virtual bool isLeaveGameDone();

    /**@vIndex {4}*/
    MC virtual WeakRef<Dimension> getOrCreateDimension(DimensionType);

    /**@vIndex {5}*/
    MC virtual WeakRef<Dimension> getDimension(DimensionType) const;

    /**
    * @vIndex {6}
    * @brief Validates that the DimensionType != Undefined, in that case resets it to the Overworld
    */
    MC virtual DimensionType getLastOrDefaultSpawnDimensionId(DimensionType) const;

    /**@vIndex {7}*/
    MC virtual void _unknown_7();

    /**@vIndex {8}*/
    MC virtual void _unknown_8();

    /**@vIndex {9}*/
    MC virtual void _unknown_9();

    /**@vIndex {10}*/
    MC virtual void _unknown_10();

    /**@vIndex {11}*/
    MC virtual unsigned int getChunkTickRange() const;

    /**@vIndex {12}*/
    MC virtual const ChunkTickRangeManager& getChunkTickRangeManager() const;

    /**@vIndex {13}*/
    MC virtual PortalForcer& getPortalForcer();

    /**@vIndex {14}*/
    MC virtual void requestPlayerChangeDimension(Player&, ChangeDimensionRequest&&);

    /**@vIndex {15}*/
    MC virtual void entityChangeDimension(Actor&, DimensionType, std::optional<Vec3>);

    /**@vIndex {16}*/
    MC virtual Spawner& getSpawner() const;

    /**@vIndex {17}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<BossEventSubscriptionManager>> getBossEventSubscriptionManager();

    /**@vIndex {18}*/
    MC virtual ProjectileFactory& getProjectileFactory() const;

    /**@vIndex {19}*/
    MC virtual ActorDefinitionGroup* getEntityDefinitions() const;

    /**@vIndex {20}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<ActorAnimationGroup>> getActorAnimationGroup() const;

    /**@vIndex {21}*/
    MC virtual Bedrock::NonOwnerPointer<ActorAnimationControllerGroup> getActorAnimationControllerGroup() const;

    /**@vIndex {22}*/
    MC virtual BlockDefinitionGroup* getBlockDefinitions() const;

    /**@vIndex {23}*/
    MC virtual void _unknown_23();

    /**@vIndex {24}*/
    MC virtual void _unknown_24();

    /**@vIndex {25}*/
    MC virtual PropertyGroupManager& getActorPropertyGroup() const;

    /**@vIndex {26}*/
    MC virtual void _unknown_26();

    /**@vIndex {27}*/
    MC virtual void _unknown_27();

    /**@vIndex {28}*/
    MC virtual bool getDisablePlayerInteractions() const;

    /**@vIndex {29}*/
    MC virtual void setDisablePlayerInteractions(bool);

    /**@vIndex {30}*/
    MC virtual AutomationBehaviorTreeGroup& getAutomationBehaviorTreeGroup() const;

    /**@vIndex {31}*/
    MC virtual BehaviorFactory& getBehaviorFactory() const;

    /**@vIndex {32}*/
    MC virtual Difficulty getDifficulty() const;

    /**@vIndex {33}*/
    MC virtual InternalComponentRegistry& getInternalComponentRegistry() const;

    /**@vIndex {34}*/
    MC virtual DimensionConversionData getDimensionConversionData() const;

    /**@vIndex {35}*/
    MC virtual float getSpecialMultiplier(DimensionType) const;

    /**@vIndex {36}*/
    MC virtual bool hasCommandsEnabled() const;

    /**@vIndex {37}*/
    MC virtual bool useMsaGamertagsOnly() const;

    /**@vIndex {38}*/
    MC virtual void setMsaGamertagsOnly(bool);

    /**@vIndex {39}*/
    MC virtual Actor* addEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {40}*/
    MC virtual Actor* addGlobalEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {41}*/
    MC virtual Actor* addAutonomousEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {42}*/
    MC virtual void addUser(OwnerPtr<EntityContext>);

    /**@vIndex {43}*/
    MC virtual Actor* addDisplayEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {44}*/
    MC virtual void removeDisplayEntity(WeakEntityRef);

    /**@vIndex {45}*/
    MC virtual void suspendPlayer(Player&);

    /**@vIndex {46}*/
    MC virtual void resumePlayer(Player&);

    /**@vIndex {47}*/
    MC virtual bool isPlayerSuspended(Player&) const;

    /**@vIndex {48}*/
    MC virtual OwnerPtr<EntityContext> removeActorAndTakeEntity(WeakEntityRef);

    /**@vIndex {49}*/
    MC virtual OwnerPtr<EntityContext> removeActorFromWorldAndTakeEntity(WeakEntityRef);

    /**@vIndex {50}*/
    MC virtual OwnerPtr<EntityContext> takeEntity(WeakEntityRef, LevelChunk&);

    /**@vIndex {51}*/
    MC virtual StrictEntityContext fetchStrictEntity(ActorUniqueID, bool) const;

    /**@vIndex {52}*/
    MC virtual Actor* fetchEntity(ActorUniqueID uniqueId, bool getRemoved) const;

    /**@vIndex {53}*/
    MC virtual Actor* getRuntimeEntity(ActorRuntimeID, bool) const;

    /**@vIndex {54}*/
    MC virtual Mob* getMob(ActorUniqueID) const;

    /**@vIndex {55}*/
    MC virtual Player* getPlayer(const std::string&) const;

    /**@vIndex {56}*/
    MC virtual Player* getPlayer(const mce::UUID&) const;

    /**@vIndex {57}*/
    MC virtual Player* getPlayer(ActorUniqueID) const;

    /**@vIndex {58}*/
    MC virtual Player* getPlayerByXuid(const std::string&) const;

    /**@vIndex {59}*/
    MC virtual Player* getPlatformPlayer(const std::string&) const;

    /**@vIndex {60}*/
    MC virtual Player* getPlayerFromServerId(const std::string&) const;

    /**@vIndex {61}*/
    MC virtual Player* getRuntimePlayer(ActorRuntimeID) const;

    /**@vIndex {62}*/
    MC virtual int getNumRemotePlayers();

    /// @vidx {63}
    /// Returns the primary local player (DOES NOT WORK FROM SERVER LEVEL)
    MC virtual Player* getPrimaryLocalPlayer() const;

    /**@vIndex {64}*/
    MC virtual IMinecraftEventing& getEventing();

    /**@vIndex {65}*/
    MC virtual mce::Color getPlayerColor(const Player&) const;

    /**@vIndex {66}*/
    MC virtual const Tick& getCurrentTick() const;

    /**@vIndex {67}*/
    MC virtual const Tick getCurrentServerTick() const;

    /**@vIndex {68}*/
    MC virtual void _unknown_68();

    /**@vIndex {69}*/
    MC virtual void _unknown_69();

    /**@vIndex {70}*/
    MC virtual BlockPalette& getBlockPalette() const;

    /**@vIndex {71}*/
    MC virtual void _unknown_71();

    /**@vIndex {72}*/
    MC virtual void _unknown_72();

    /**@vIndex {73}*/
    MC virtual void _unknown_73();

    /**@vIndex {74}*/
    MC virtual void _unknown_74();

    /**@vIndex {75}*/
    MC virtual void _unknown_75();

    /**@vIndex {76}*/
    MC virtual void _unknown_76();

    /**@vIndex {77}*/
    MC virtual void _unknown_77();

    /**@vIndex {78}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager();

    /**@vIndex {79}*/
    MC virtual const gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager() const;

    /**@vIndex {80}*/
    MC virtual void _unknown_80();

    /**@vIndex {81}*/
    MC virtual void _unknown_81();

    /**@vIndex {82}*/
    MC virtual void _unknown_82();

    /**@vIndex {83}*/
    MC virtual void _unknown_83();

    /**@vIndex {84}*/
    MC virtual BiomeManager& getBiomeManager();

    /**@vIndex {85}*/
    MC virtual const BiomeManager& getBiomeManager() const;

    /**@vIndex {86}*/
    MC virtual void _unknown_86();

    /**@vIndex {87}*/
    MC virtual void _unknown_87();

    /**@vIndex {88}*/
    MC virtual void _unknown_88();

    /**@vIndex {89}*/
    MC virtual void _unknown_89();

    /**@vIndex {90}*/
    MC virtual void _unknown_90();

    /**@vIndex {91}*/
    MC virtual void _unknown_91();

    /**@vIndex {92}*/
    MC virtual void addListener(LevelListener&);

    /**@vIndex {93}*/
    MC virtual void removeListener(LevelListener&);

    /**@vIndex {94}*/
    MC virtual void tickEntities();

    /**@vIndex {95}*/
    MC virtual void tickEntitySystems();

    /**@vIndex {96}*/
    MC virtual void _unknown_96();

    /**@vIndex {97}*/
    MC virtual void _unknown_97();

    /**@vIndex {98}*/
    MC virtual void onPlayerDeath(Player&, const ActorDamageSource&);

    /**@vIndex {99}*/
    MC virtual void tick();

    /**@vIndex {100}*/
    MC virtual bool explode(Explosion&);

    /**@vIndex {101}*/
    MC virtual bool explode(BlockSource&, Actor*, const Vec3&, float, bool, bool, float, bool);

    /**@vIndex {102}*/
    MC virtual void spawnParticleEffect(const std::string&, const Vec3&, Dimension*);

    /**@vIndex {103}*/
    MC virtual void denyEffect(BlockSource&, const Vec3&);

    /**@vIndex {104}*/
    MC virtual void potionSplash(const Vec3&, const mce::Color&, bool);

    /**@vIndex {105}*/
    MC virtual bool extinguishFire(BlockSource&, const BlockPos&, unsigned char, Actor*);

    /**@vIndex {106}*/
    MC virtual std::unique_ptr<Path> findPath(Actor&, Actor&, NavigationComponent&);

    /**@vIndex {107}*/
    MC virtual std::unique_ptr<Path> findPath(Actor&, int, int, int, NavigationComponent&);

    /**@vIndex {108}*/
    MC virtual void updateSleepingPlayerList();

    /**@vIndex {109}*/
    MC virtual void setSleepStatus(const PlayerSleepStatus&);

    /**@vIndex {110}*/
    MC virtual PlayerSleepStatus getSleepStatus() const;

    /**@vIndex {111}*/
    MC virtual int getTime() const;

    /**@vIndex {112}*/
    MC virtual void setTime(int);

    /**@vIndex {113}*/
    MC virtual unsigned int getSeed();

    /**@vIndex {114}*/
    MC virtual const BlockPos& getDefaultSpawn() const;

    /**@vIndex {115}*/
    MC virtual void setDefaultSpawn(const BlockPos&);

    /**@vIndex {116}*/
    MC virtual void _unknown_116();

    /**@vIndex {117}*/
    MC virtual void setDefaultGameType(GameType);

    /**@vIndex {118}*/
    MC virtual GameType getDefaultGameType() const;

    /**@vIndex {119}*/
    MC virtual void setDifficulty(Difficulty);

    /**@vIndex {120}*/
    MC virtual void setMultiplayerGameIntent(bool);

    /**@vIndex {121}*/
    MC virtual bool getMultiplayerGameIntent() const;

    /**@vIndex {122}*/
    MC virtual void setMultiplayerGame(bool);

    /**@vIndex {123}*/
    MC virtual bool isMultiplayerGame() const;

    /**@vIndex {124}*/
    MC virtual void setLANBroadcastIntent(bool);

    /**@vIndex {125}*/
    MC virtual bool getLANBroadcastIntent() const;

    /**@vIndex {126}*/
    MC virtual void setLANBroadcast(bool);

    /**@vIndex {127}*/
    MC virtual bool getLANBroadcast() const;

    /**@vIndex {128}*/
    MC virtual void setXBLBroadcastIntent(Social::GamePublishSetting);

    /**@vIndex {129}*/
    MC virtual Social::GamePublishSetting getXBLBroadcastIntent() const;

    /**@vIndex {130}*/
    MC virtual bool hasXBLBroadcastIntent() const;

    /**@vIndex {131}*/
    MC virtual void setXBLBroadcastMode(Social::GamePublishSetting);

    /**@vIndex {132}*/
    MC virtual Social::GamePublishSetting getXBLBroadcastMode() const;

    /**@vIndex {133}*/
    MC virtual bool hasXBLBroadcast() const;

    /**@vIndex {134}*/
    MC virtual void setPlatformBroadcastIntent(Social::GamePublishSetting);

    /**@vIndex {135}*/
    MC virtual Social::GamePublishSetting getPlatformBroadcastIntent() const;

    /**@vIndex {136}*/
    MC virtual bool hasPlatformBroadcastIntent() const;

    /**@vIndex {137}*/
    MC virtual void setPlatformBroadcastMode(Social::GamePublishSetting);

    /**@vIndex {138}*/
    MC virtual Social::GamePublishSetting getPlatformBroadcastMode() const;

    /**@vIndex {139}*/
    MC virtual bool hasPlatformBroadcast() const;

    /**@vIndex {140}*/
    MC virtual void setHasLockedBehaviorPack(bool);

    /**@vIndex {141}*/
    MC virtual void setHasLockedResourcePack(bool);

    /**@vIndex {142}*/
    MC virtual void setCommandsEnabled(bool);

    /**@vIndex {143}*/
    MC virtual void setWorldTemplateOptionsUnlocked();

    /**@vIndex {144}*/
    MC virtual bool hasLevelStorage() const;

    /**@vIndex {145}*/
    MC virtual void _unknown_145();

    /**@vIndex {146}*/
    MC virtual void _unknown_146();

    /**@vIndex {147}*/
    MC virtual LevelData& getLevelData();

    /**@vIndex {148}*/
    MC virtual const LevelData& getLevelData() const;

    /**@vIndex {149}*/
    MC virtual PhotoStorage& getPhotoStorage();

    /**@vIndex {150}*/
    MC virtual void createPhotoStorage();

    /**@vIndex {151}*/
    MC virtual void setEducationLevelSettings(EducationLevelSettings);

    /**@vIndex {152}*/
    MC virtual const std::optional<EducationLevelSettings>& getEducationLevelSettings() const;

    /**@vIndex {153}*/
    MC virtual void save();

    /**@vIndex {154}*/
    MC virtual void saveLevelData();

    /**@vIndex {155}*/
    MC virtual void saveGameData();

    /**@vIndex {156}*/
    MC virtual std::shared_ptr<void*> requestTimedStorageDeferment();

    /**@vIndex {157}*/
    MC virtual TickingAreasManager& getTickingAreasMgr();

    /**@vIndex {158}*/
    MC virtual void addTickingAreaList(DimensionType, const std::shared_ptr<TickingAreaList>&);

    /**@vIndex {159}*/
    MC virtual void sendServerLegacyParticle(ParticleType, const Vec3&, const Vec3&, int);

    /**@vIndex {160}*/
    MC virtual void playSound(DimensionType, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {161}*/
    MC virtual void playSound(const IConstBlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {162}*/
    MC virtual void playSound(const std::string&, const Vec3&, float, float);

    /**@vIndex {163}*/
    MC virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, float, float);

    /**@vIndex {164}*/
    MC virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {165}*/
    MC virtual PlayerEventCoordinator& getRemotePlayerEventCoordinator();

    /**@vIndex {166}*/
    MC virtual ServerPlayerEventCoordinator& getServerPlayerEventCoordinator();

    /**@vIndex {167}*/
    MC virtual ClientPlayerEventCoordinator& getClientPlayerEventCoordinator();

    /**@vIndex {168}*/
    MC virtual ActorEventCoordinator& getActorEventCoordinator();

    /**@vIndex {169}*/
    MC virtual BlockEventCoordinator& getBlockEventCoordinator();

    /**@vIndex {170}*/
    MC virtual ItemEventCoordinator& getItemEventCoordinator();

    /**@vIndex {171}*/
    MC virtual ServerNetworkEventCoordinator& getServerNetworkEventCoordinator();

    /**@vIndex {172}*/
    MC virtual ScriptingEventCoordinator& getScriptingEventCoordinator();

    /**@vIndex {173}*/
    MC virtual ScriptDeferredEventCoordinator& getScriptDeferredEventCoordinator();

    /**@vIndex {174}*/
    MC virtual LevelEventCoordinator& getLevelEventCoordinator();

    /**@vIndex {175}*/
    MC virtual void handleLevelEvent(LevelEvent, const CompoundTag&);

    /**@vIndex {176}*/
    MC virtual void handleLevelEvent(LevelEvent, const Vec3&, int);

    /**@vIndex {177}*/
    MC virtual void handleStopSoundEvent(const std::string&);

    /**@vIndex {178}*/
    MC virtual void handleStopAllSounds();

    /**@vIndex {179}*/
    MC virtual void broadcastLevelEvent(LevelEvent, const CompoundTag&, const UserEntityIdentifierComponent*);

    /**@vIndex {180}*/
    MC virtual void broadcastLevelEvent(LevelEvent, const Vec3&, int, const UserEntityIdentifierComponent*);

    /**@vIndex {181}*/
    MC virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, const Block&);

    /**@vIndex {182}*/
    MC virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, int);

    /**@vIndex {183}*/
    MC virtual void broadcastSoundEvent(Dimension&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {184}*/
    MC virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {185}*/
    MC virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, const Block&, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {186}*/
    MC virtual void broadcastActorEvent(Actor&, ActorEvent, int) const;

    /**@vIndex {187}*/
    MC virtual void addChunkViewTracker(std::weak_ptr<ChunkViewSource>);

    /**@vIndex {188}*/
    MC virtual void onChunkReload(const Bounds&);

    /**@vIndex {189}*/
    MC virtual void onChunkReloaded(ChunkSource&, LevelChunk&);

    /**@vIndex {190}*/
    MC virtual int getActivePlayerCount() const;

    /**@vIndex {191}*/
    MC virtual int getActiveUsersCount() const;

    /**@vIndex {192}*/
    MC virtual void forEachPlayer(std::function<bool(Player&)>);

    /**@vIndex {193}*/
    MC virtual void forEachPlayer(std::function<bool(const Player&)>) const;

    /**@vIndex {194}*/
    MC virtual void forEachUser(std::function<bool(const EntityContext&)>) const;

    /**@vIndex {195}*/
    MC virtual void forEachUser(std::function<bool(EntityContext&)>);

    /**@vIndex {196}*/
    MC virtual Player* findPlayer(std::function<bool(const WeakEntityRef&)>) const;

    /**@vIndex {197}*/
    MC virtual Player* findPlayer(std::function<bool(const Player&)>) const;

    /**@vIndex {198}*/
    MC virtual int getUserCount() const;

    /**@vIndex {199}*/
    MC virtual int countUsersWithMatchingNetworkId(const NetworkIdentifier&) const;

    /**@vIndex {200}*/
    MC virtual const std::vector<OwnerPtr<EntityContext>>& getUsers() const;

    /**@vIndex {201}*/
    MC virtual const std::vector<OwnerPtr<EntityContext>>& getEntities() const;

    /**@vIndex {202}*/
    MC virtual void _unknown_202();

    /**@vIndex {203}*/
    MC virtual void onChunkLoaded(ChunkSource&, LevelChunk&);

    /**@vIndex {204}*/
    MC virtual void onChunkDiscarded(LevelChunk&);

    /**@vIndex {205}*/
    MC virtual void _unknown_205();

    /**@vIndex {206}*/
    MC virtual void queueEntityDestruction(OwnerPtr<EntityContext>);

    /**@vIndex {207}*/
    MC virtual OwnerPtr<EntityContext> removeEntity(WeakEntityRef);

    /**@vIndex {208}*/
    MC virtual OwnerPtr<EntityContext> removeEntity(Actor&);

    /**@vIndex {209}*/
    MC virtual void forceRemoveEntity(Actor&);

    /**@vIndex {210}*/
    MC virtual void forceRemoveEntityfromWorld(Actor&);

    /**@vIndex {211}*/
    MC virtual void forceFlushRemovedPlayers();

    /**@vIndex {212}*/
    MC virtual void _unknown_212();

    /**@vIndex {213}*/
    MC virtual void levelCleanupQueueEntityRemoval(OwnerPtr<EntityContext>);

    /**@vIndex {214}*/
    MC virtual void registerTemporaryPointer(_TickPtr&);

    /**@vIndex {215}*/
    MC virtual void unregisterTemporaryPointer(_TickPtr&);

    /**@vIndex {216}*/
    MC virtual bool destroyBlock(BlockSource&, const BlockPos&, bool);

    /**@vIndex {217}*/
    MC virtual void upgradeStorageVersion(StorageVersion);

    /**@vIndex {218}*/
    MC virtual void suspendAndSave();

    /**@vIndex {219}*/
    MC virtual Particle* addParticle(ParticleType, const Vec3&, const Vec3&, int, const CompoundTag*, bool);

    /**@vIndex {220}*/
    MC virtual void _destroyEffect(const BlockPos&, const Block&, int);

    /**@vIndex {221}*/
    MC virtual void addParticleEffect(const HashedString&, const Vec3&, const MolangVariableMap&);

    /**@vIndex {222}*/
    MC virtual void addTerrainParticleEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vIndex {223}*/
    MC virtual void addTerrainSlideEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vIndex {224}*/
    MC virtual void addBreakingItemParticleEffect(const Vec3&, ParticleType, const ResolvedItemIconInfo&);

    /**@vIndex {225}*/
    MC virtual ActorUniqueID getNewUniqueID();

    /**@vIndex {226}*/
    MC virtual ActorRuntimeID getNextRuntimeID();

    /**@vIndex {227}*/
    MC virtual const std::vector<ChunkPos>& getTickingOffsets() const;

    /**@vIndex {228}*/
    MC virtual const std::vector<ChunkPos>& getClientTickingOffsets() const;

    /**@vIndex {229}*/
    MC virtual std::vector<ChunkPos> getSortedPositionsFromClientOffsets(const std::vector<ChunkPos>&) const;

    /**@vIndex {230}*/
    MC virtual bool isExporting() const;

    /**@vIndex {231}*/
    MC virtual void setIsExporting(bool);

    /**@vIndex {232}*/
    MC virtual SavedDataStorage& getSavedData();

    /**@vIndex {233}*/
    MC virtual void _unknown_233();

    /**@vIndex {234}*/
    MC virtual void _unknown_234();

    /**@vIndex {235}*/
    MC virtual MapItemSavedData* getMapSavedData(ActorUniqueID);

    /**@vIndex {236}*/
    MC virtual void requestMapInfo(ActorUniqueID, bool);

    /**@vIndex {237}*/
    MC virtual ActorUniqueID expandMapByID(ActorUniqueID, bool);

    /**@vIndex {238}*/
    MC virtual bool copyAndLockMap(ActorUniqueID, ActorUniqueID);

    /**@vIndex {239}*/
    MC virtual MapItemSavedData& createMapSavedData(const std::vector<ActorUniqueID>&, const BlockPos&, DimensionType, int);

    /**@vIndex {240}*/
    MC virtual MapItemSavedData& createMapSavedData(const ActorUniqueID&, const BlockPos&, DimensionType, int);

    /**@vIndex {241}*/
    MC virtual Core::PathBuffer<std::string> getScreenshotsFolder() const;

    /**@vIndex {242}*/
    MC virtual std::string getLevelId() const;

    /**@vIndex {243}*/
    MC virtual void setLevelId(std::string);

    /**@vIndex {244}*/
    MC virtual TaskGroup& getSyncTasksGroup();

    /**@vIndex {245}*/
    MC virtual TaskGroup& getIOTasksGroup();

    /**@vIndex {246}*/
    MC virtual void _unknown_246();

    /**@vIndex {247}*/
    MC virtual void _unknown_247();

    /**@vIndex {248}*/
    MC virtual void _unknown_248();

    /**@vIndex {249}*/
    MC virtual void _unknown_249();

    /**@vIndex {250}*/
    MC virtual void _unknown_250();

    /**@vIndex {251}*/
    MC virtual bool isEdu() const;

    /**@vIndex {252}*/
    MC virtual void _unknown_252();

    /**@vIndex {253}*/
    MC virtual void _unknown_253();

    /**@vIndex {254}*/
    MC virtual ActorInfoRegistry* getActorInfoRegistry();

    /**@vIndex {255}*/
    //MC virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    MC virtual void _unknown_255();

    /**@vIndex {256}*/
    //MC virtual StackRefResult<EntityRegistry> getEntityRegistry();
    MC virtual void _unknown_256();

    /**@vIndex {257}*/
    MC virtual EntitySystems& getEntitySystems();

    /**@vIndex {258}*/
    MC virtual WeakRef<EntityContext> getLevelEntity();

    /**@vIndex {259}*/
    MC virtual void _unknown_259();

    /**@vIndex {260}*/
    MC virtual void _unknown_260();

    /**@vIndex {261}*/
    MC virtual const PlayerCapabilities::ISharedController& getCapabilities() const;

    /**@vIndex {262}*/
    //MC virtual TagRegistry<IDType<LevelTagIDType>, IDType<LevelTagSetIDType>>& getTagRegistry();
    MC virtual void _unknown_262();

    /**@vIndex {263}*/
    MC virtual const PlayerMovementSettings& getPlayerMovementSettings() const;

    /**@vIndex {264}*/
    MC virtual void setPlayerMovementSettings(const PlayerMovementSettings&);

    /**@vIndex {265}*/
    MC virtual bool canUseSkin(const SerializedSkin&, const NetworkIdentifier&, const mce::UUID&, const ActorUniqueID&) const;

    /**@vIndex {266}*/
    MC virtual PositionTrackingDB::PositionTrackingDBClient* getPositionTrackerDBClient() const;

    /**@vIndex {267}*/
    MC virtual void _unknown_267();

    /**@vIndex {268}*/
    MC virtual void flushRunTimeLighting();

    /**@vIndex {269}*/
    MC virtual void loadBlockDefinitionGroup(const Experiments&);

    /**@vIndex {270}*/
    MC virtual void initializeBlockDefinitionGroup();

    /**@vIndex {271}*/
    MC virtual Bedrock::NonOwnerPointer<IUnknownBlockTypeRegistry> getUnknownBlockTypeRegistry();

    /**@vIndex {272}*/
    MC virtual bool isClientSide() const;

    /**@vIndex {273}*/
    MC virtual void _unknown_273();

    /**@vIndex {274}*/
    MC virtual void _unknown_274();

    /**@vIndex {275}*/
    MC virtual const std::string& getPlayerXUID(const mce::UUID&) const;

    /**@vIndex {276}*/
    MC virtual const std::string& getPlayerPlatformOnlineId(const mce::UUID&) const;

    /**@vIndex {277}*/
    MC virtual const std::vector<WeakEntityRef>& getActiveUsers() const;

    /**@vIndex {278}*/
    MC virtual std::vector<Actor*> getRuntimeActorList() const;

    /**@vIndex {279}*/
    MC virtual void _unknown_279();

    /**@vIndex {280}*/
    MC virtual void _unknown_280();

    /**@vIndex {281}*/
    MC virtual PacketSender* getPacketSender() const;

    /**@vIndex {282}*/
    MC virtual void setPacketSender(PacketSender*);

    /**@vIndex {283}*/
    MC virtual Bedrock::NonOwnerPointer<NetEventCallback> getNetEventCallback() const;

    /**@vIndex {284}*/
    MC virtual void setNetEventCallback(Bedrock::NonOwnerPointer<NetEventCallback>);

    /**@vIndex {285}*/
    MC virtual void _unknown_285();

    /**@vIndex {286}*/
    MC virtual void _unknown_286();

    /**@vIndex {287}*/
    MC virtual void _unknown_287();

    /**@vIndex {288}*/
    MC virtual HitResult& getHitResult();

    /**@vIndex {289}*/
    MC virtual HitResult& getLiquidHitResult();

    /**@vIndex {290}*/
    MC virtual const std::string& getImmersiveReaderString() const;

    /**@vIndex {291}*/
    MC virtual void setImmersiveReaderString(std::string);

    /**@vIndex {292}*/
    MC virtual const AdventureSettings& getAdventureSettings() const;

    /**@vIndex {293}*/
    MC virtual AdventureSettings& getAdventureSettings();

    /**@vIndex {294}*/
    MC virtual GameRules& getGameRules();

    /**@vIndex {295}*/
    MC virtual const GameRules& getGameRules() const;

    /**@vIndex {296}*/
    MC virtual bool hasStartWithMapEnabled() const;

    /**@vIndex {297}*/
    MC virtual bool isEditorWorld() const;

    /**@vIndex {298}*/
    MC virtual Abilities& getDefaultAbilities();

    /**@vIndex {299}*/
    MC virtual const PermissionsHandler& getDefaultPermissions() const;

    /**@vIndex {300}*/
    MC virtual PermissionsHandler& getDefaultPermissions();

    /**@vIndex {301}*/
    MC virtual bool getTearingDown() const;

    /**@vIndex {302}*/
    MC virtual void takePicture(cg::ImageBuffer&, Actor*, Actor*, ScreenshotOptions&);

    /**@vIndex {303}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<LevelSoundManager>> getLevelSoundManager();

    /**@vIndex {304}*/
    MC virtual gsl::not_null<Bedrock::NonOwnerPointer<SoundPlayerInterface>> getSoundPlayer() const;

    /**@vIndex {305}*/
    MC virtual void setSimPaused(bool);

    /**@vIndex {306}*/
    MC virtual bool getSimPaused();

    /**@vIndex {307}*/
    MC virtual void setFinishedInitializing();

    /**@vIndex {308}*/
    MC virtual LootTables& getLootTables();

    /**@vIndex {309}*/
    MC virtual void updateWeather(float, int, float, int);

    /**@vIndex {310}*/
    MC virtual int getNetherScale() const;

    /**@vIndex {311}*/
    MC virtual void _unknown_311();

    /**@vIndex {312}*/
    MC virtual void _unknown_312();

    /**@vIndex {313}*/
    MC virtual void _unknown_313();

    /**@vIndex {314}*/
    MC virtual LayeredAbilities* getPlayerAbilities(const ActorUniqueID&);

    /**@vIndex {315}*/
    MC virtual void setPlayerAbilities(const ActorUniqueID&, const LayeredAbilities&);

    /**@vIndex {316}*/
    MC virtual void sendAllPlayerAbilities(const Player&);

    /**@vIndex {317}*/
    MC virtual Recipes& getRecipes() const;

    /**@vIndex {318}*/
    MC virtual BlockReducer* getBlockReducer() const;

    /**@vIndex {319}*/
    MC virtual void _unknown_319();

    /**@vIndex {320}*/
    MC virtual void _unknown_320();

    /**@vIndex {321}*/
    MC virtual void _unknown_321();

    /**@vIndex {322}*/
    MC virtual void _unknown_322();

    /**@vIndex {323}*/
    MC virtual void digestServerItemComponents(const ItemComponentPacket&);

    /**@vIndex {324}*/
    MC virtual const BlockLegacy& getRegisteredBorderBlock() const;

    /**@vIndex {325}*/
    MC virtual bool use3DBiomeMaps() const;

    /**@vIndex {326}*/
    MC virtual void addBlockSourceForValidityTracking(BlockSource*);

    /**@vIndex {327}*/
    MC virtual void removeBlockSourceFromValidityTracking(BlockSource*);

    /**@vIndex {328}*/
    MC virtual Level* asLevel();

    /**@vIndex {329}*/
    MC virtual void _unknown_329();

    /**@vIndex {330}*/
    MC virtual bool isClientSideGenerationEnabled();

    /**@vIndex {331}*/
    MC virtual bool blockNetworkIdsAreHashes();

    /**@vIndex {332}*/
    MC virtual ItemRegistryRef getItemRegistry() const;

    /**@vIndex {333}*/
    MC virtual std::weak_ptr<BlockTypeRegistry> getBlockRegistry() const;

    /**@vIndex {334}*/
    MC virtual void pauseAndFlushTaskGroups();

    /**@vIndex {335}*/
    MC virtual void _unknown_335();

    /**@vIndex {336}*/
    MC virtual void _unknown_336();

    /**@vIndex {337}*/
    MC virtual void _unknown_337();

    /**@vIndex {338}*/
    MC virtual void _unknown_338();

    /**@vIndex {339}*/
    MC virtual void _unknown_339();

protected:
    /**@vIndex {340}*/
    MC virtual void _subTick();

    /**@vIndex {341}*/
    MC virtual void _initializeMapDataManager();
};