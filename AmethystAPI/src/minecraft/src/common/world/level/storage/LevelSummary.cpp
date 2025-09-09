#include "LevelSummary.hpp"

LevelSummary::LevelSummary(const std::string& id, const LevelData& levelData, const Core::Path& a4, const Core::Path& a5, bool a6)
{
    mId = id;
    mName = levelData.mLevelName;
    mLastSaved = levelData.mLastSaved;

    mGameType = levelData.getGameType();
    mIsHardcore = levelData.mIsHardcore;
    mGameDifficulty = levelData.mGameDifficulty;
    mSeed = levelData.getSeed();

    mNetworkProtocolVersion = levelData.mNetworkVersion;
    mConfirmedPlatformLockedContent = levelData.mConfirmedPlatformLockedContent;
    mIsMultiplayerEnabled = levelData.mMultiplayerGameIntent;
    mLANBroadcastIntent = levelData.mLANBroadcastIntent;
    mXBLBroadcastIntent = levelData.mXBLBroadcastIntent;
    mCommandsEnabled = levelData.mCommandsEnabled;
    mEducationEditionOffer = levelData.mEducationEditionOffer;

    mLastLoadedGameVersion = levelData.mLastOpenedWithVersion;
    mMinCompatibleClientVersion = levelData.mMinCompatibleClientVersion;
    mStorageVersion = levelData.mStorageVersion;

    mWorldIconPath = Core::PathBuffer<std::string>();
    mWorldIconTargetPath = Core::PathBuffer<std::string>();

    mPremiumTemplateContentIdentity = levelData.mWorldTemplateLevelData.mPremiumTemplateContentIdentity;
    mEducationOid = levelData.getEducationOid();

    mExperiments = levelData.mExperiments;

    mIsSingleUseWorld = levelData.mIsSingleUseWorld;
    mIsBetaRetailLevel = a6;

    mEduSharedUriResource.buttonName = "";
    mEduSharedUriResource.linkUri = "";
    mEditorWorldType = levelData.mEditorWorldType;

    // TODO NEED TO CALL Core::FileSystem::getFileOrDirectorySize(v22, a4, self + 104);

    // AND

    // LevelSummary::_initializeWorldIconPath(self, v18);
    mSizeOnDisk = 0;

    mCloudSaveInfo = std::nullopt;
    mEduCloudWorldSyncState = EduCloud::WorldSyncState::None;
}
