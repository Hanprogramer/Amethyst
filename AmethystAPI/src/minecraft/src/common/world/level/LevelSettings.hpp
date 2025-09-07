#pragma once
#include <string>
#include <minecraft/src/common/world/level/GameType.hpp>
#include <minecraft/src/common/util/NewType.hpp>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <vector>
#include <optional>
#include <minecraft/src/common/world/level/BlockPos.hpp>
#include <minecraft/src-deps/core/resource/ResourceHelper.hpp>
#include <minecraft/src/common/world/level/storage/GameRules.hpp>
#include <minecraft/src/common/resources/BaseGameVersion.hpp>

enum class GeneratorType : int {
    Legacy    = 0,
    Overworld = 1,
    Flat      = 2,
    Nether    = 3,
    TheEnd    = 4,
    Void      = 5,
    Undefined = 6,
};

class EducationEditionOfferValue {
    std::byte padding0[4];
};

enum class WorldVersion : uint8_t {
    Pre1_18  = 0,
    Post1_18 = 1,
};

enum class SpawnBiomeType : short {
    Default     = 0,
    UserDefined = 1,
};

struct SpawnSettings
{
    SpawnBiomeType type;
    std::string userDefinedBiomeName;
    DimensionType dimension;
};

class LevelSeed64 {
public:
    uint64_t mValue;
};

namespace Editor {
enum class WorldType : int {
    NonEditor          = 0,
    EditorProject      = 1,
    EditorTestLevel    = 2,
    EditorRealmsUpload = 3,
};
}

namespace Social {
enum class GamePublishSetting : int {
    NoMultiPlay      = 0,
    InviteOnly       = 1,
    FriendsOnly      = 2,
    FriendsOfFriends = 3,
    Public           = 4,
};
}

enum class CommandPermissionLevel : uint8_t {
    Any           = 0,
    GameDirectors = 1,
    Admin         = 2,
    Host          = 3,
    Owner         = 4,
    Internal      = 5,
};

enum class PlayerPermissionLevel : int8_t {
    Visitor  = 0,
    Member   = 1,
    Operator = 2,
    Custom   = 3,
};

class PermissionsHandler {
public:
    CommandPermissionLevel mCommandPermissions;
    PlayerPermissionLevel mPlayerPermissions;
};

enum class Difficulty : int32_t {
    Peaceful = 0x0000,
    Easy = 0x0001,
    Normal = 0x0002,
    Hard = 0x0003,
    Count = 0x0004,
    Unknown = 0x0005,
};

enum class NetherWorldType : uint8_t {
    Normal = 0,
    Flat   = 1,
};

enum class DaylightCycle : uint8_t {
    Normal    = 0,
    AlwaysDay = 1,
    LockTime  = 2,
};

struct PackInstanceId {
    PackIdVersion mPackId;
    std::string mSubpackName;
};

class ExperimentStorage {
public:
    std::vector<bool> mExperimentData;
    std::vector<bool> mDeprecatedData;
    bool mExperimentsEverToggled;
};

struct EduSharedUriResource {
    std::string linkUri;
    std::string buttonName;
};

enum class ForceBlockNetworkIdsAreHashes : uint8_t {
    UseDefault = 0,
    ForceOff   = 1,
    ForceOn    = 2,
};

enum class ChatRestrictionLevel : uint8_t {
    None     = 0,
    Dropped  = 1,
    Disabled = 2,
};

class CloudSaveLevelInfo {
    std::byte padding0[176 - 1];
};

class EducationLevelSettings {
    std::byte padding0[328 - 1];
};

class LevelSettings {
public:
    LevelSeed64 mSeed;
    GameType mGameType;
    bool mIsHardcore;
    Difficulty mGameDifficulty;
    bool mForceGameType;
    GeneratorType mGenerator;
    WorldVersion mWorldVersion;
    NetherWorldType mNetherType;
    SpawnSettings mSpawnSettings;
    bool mAchievementsDisabled;
    Editor::WorldType mEditorWorldType;
    bool mIsCreatedInEditor;
    bool mIsExportedFromEditor;
    int mTime;
    EducationEditionOfferValue mEducationEditionOffer;
    bool mEducationFeaturesEnabled;
    bool mImmutableWorld;
    float mRainLevel;
    float mLightningLevel;
    bool mConfirmedPlatformLockedContent;
    bool mMultiplayerGameIntent;
    bool mLANBroadcastIntent;
    Social::GamePublishSetting mXBLBroadcastIntent;
    Social::GamePublishSetting mPlatformBroadcastIntent;
    DaylightCycle mDaylightCycle;
    bool mDisablePlayerInteractions;
    bool mCheatsEnabled;
    bool mAdventureModeOverridesEnabled;
    bool mCommandsEnabled;
    bool mTexturePacksRequired;
    bool mHasLockedBehaviorPack;
    bool mHasLockedResourcePack;
    bool mIsFromLockedTemplate;
    bool mIsRandomSeedAllowed;
    bool mUseMsaGamertagsOnly;
    bool mOverrideSettings;
    bool mBonusChestEnabled;
    bool mStartWithMapEnabled;
    int mServerChunkTickRange;
    bool mIsFromWorldTemplate;
    bool mIsWorldTemplateOptionLocked;
    bool mSpawnV1Villagers;
    bool mPersonaDisabled;
    bool mCustomSkinsDisabled;
    bool mEmoteChatMuted;
    int mLimitedWorldWidth;
    int mLimitedWorldDepth;
    PermissionsHandler mDefaultPermissions;
    BlockPos mDefaultSpawn;
    std::vector<PackInstanceId> mNewWorldBehaviorPackIdentities;
    std::vector<PackInstanceId> mNewWorldResourcePackIdentities;
    GameRules mGameRules;
    ExperimentStorage mExperiments;
    BaseGameVersion mBaseGameVersion;
    std::string mEducationProductID;
    std::string mBiomeOverride;
    EduSharedUriResource mEduSharedUriResource;
    ChatRestrictionLevel mChatRestrictionLevel;
    std::string mServerId;
    std::string mWorldId;
    std::string mScenarioId;
    std::optional<EducationLevelSettings> mEducationLevelSettings;
    std::optional<bool> mOverrideForceExperimentalGameplayFlag;
    std::optional<CloudSaveLevelInfo> mCloudSaveInfo;
    std::vector<std::string> mExcludedScriptModules;
    bool mAddExperiments;
    bool mOverrideBaseGameVersion;
    ForceBlockNetworkIdsAreHashes mForceBlockNetworkIdsAreHashes;
};