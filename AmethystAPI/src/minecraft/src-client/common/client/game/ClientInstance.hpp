/// @symbolgeneration
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <chrono>
#include "minecraft/src-deps/renderer/Camera.hpp"
#include "minecraft/src-client/common/client/renderer/TexturePtr.hpp"
#include "minecraft/src-deps/renderer/ViewportInfo.hpp"
#include "minecraft/src/common/gamerefs/WeakRef.hpp"
#include <amethyst/Imports.hpp>
 
class Minecraft;
class ClientInputHandler;
class ItemRenderer;
class BlockTessellator;
class FileDataRequest;
namespace Core { class Path; }
namespace Bedrock::Http { class Status; }
class MinecraftGame;
class GuiData;
class LocalPlayer;
class BlockSource;
class ToastManager; 

//is_virtual = True
//    hide_vtable = False
//        struct_size = 3232
//
//#(Type, Name, Size(in bytes), Offset(in bytes))
//    struct
//    = [("MinecraftGame*", "minecraftGame", 8, 200),
//       ("Minecraft*", "minecraft", 8, 208),
//       ("ClientInputHandler*", "inputHandler", 8, 272),
//       ("ItemRenderer*", "itemRenderer", 8, 1360),
//       ("GuiData*", "guiData", 8, 1368),
//       ("mce::Camera", "camera", 512, 624),
//       ("BlockTessellator*", "mBlockTessellator", 8, 1320)]

class LevelRenderer;
class LightTexture;
class LoopbackPacketSender;
class HolographicPlatform;
class VoiceSystem;
class ClientMoveInputHandler;
class MinecraftKeyboardManager;
class HitDetectSystem;
class UserAuthentication;
class SceneFactory;
class CachedScenes;
class BuildActionIntention;

enum class PlayScreenDefaultTab : int32_t {
    World = 0x0000,
    Friends = 0x0001,
    Servers = 0x0002,
    Count = 0x0003,
};

class Actor;

class ClientInstance {
public:
    class ClientRenderResources {
    public:
        void* mUITexture; // mce::Texture* mUITexture;
        mce::TexturePtr mUICursorTexture;
    };

    // thanks levilamina for CI!!

    /* this + 0    */ uintptr_t** vtable;
    /* this + 8    */ std::byte padding8[192];
    /* this + 200  */ MinecraftGame* minecraftGame;
    /* this + 208  */ Minecraft* minecraft;
    /* this + 216  */ bool mIsFullVanillaPackOnStack;

    /* this + 224  */ std::unique_ptr<LevelRenderer> mLevelRenderer;
    /* this + 232  */ std::unique_ptr<LightTexture> mLightTexture;
    /* this + 240  */ std::unique_ptr<LoopbackPacketSender> mPacketSender;
    /* this + 248  */ std::unique_ptr<HolographicPlatform> mHoloInput;
    /* this + 256  */ std::unique_ptr<VoiceSystem> mVoiceSystem;
    /* this + 264  */ std::unique_ptr<ClientMoveInputHandler> mClientMoveInputHandler;
    /* this + 272  */ std::unique_ptr<ClientInputHandler> mClientInputHandler;
    /* this + 280  */ std::unique_ptr<MinecraftKeyboardManager> mKeyboardManager;
    /* this + 288  */ std::unique_ptr<HitDetectSystem> mHitDetectSystem;
    /* this + 296  */ std::shared_ptr<UserAuthentication> mUserAuthentication;
    uint64_t padding304; // idk what this is!!
    /* this + 312  */ std::unique_ptr<SceneFactory> mSceneFactory; 
    /* this + 320  */ std::unique_ptr<CachedScenes> mCachedScenes;

    // Somewhere between here
    WeakEntityRef mCameraRef;
    WeakEntityRef mCameraTargetRef; 
    WeakEntityRef mLocalUser;
    std::unique_ptr<BuildActionIntention> mInProgressBai;
    float mHoloviewerScale;
    float mRealityModeFrameFactor;
    bool mRealityModeToggleTriggered;
    alignas(4) std::byte mPlayMode[4];
    bool mTickedLastFrame;
    std::atomic<bool> mOpenControllerDisconnectScreen;
    std::atomic<bool> mHandlingControllerDisconnect;
    std::atomic<bool> mConnectGamepadScreenActive;
    PlayScreenDefaultTab mDefaultPlayscreenTab;
    bool mInGameInputEnabled;
    bool mIsInUpdate;
    bool mLivingRoomCredits;
    std::function<void()> mCreditsCallback;
    std::chrono::steady_clock::time_point mNoBlockBreakUntil;
    bool mNewDictationString;
    std::string mDictation;

    std::byte padding488[16];
    // and here some size is off ^^ this pading shouldnt exist

    /* this + 552  */ ViewportInfo mViewportInfo;
    /* this + 576  */ ClientInstance::ClientRenderResources mClientRenderResources;
    /* this + 616  */ void* mLevelTexture; // mce::Texture* 
    /* this + 624  */ mce::Camera camera;
    /* this + 1136 */ std::byte padding1136[184];
    /* this + 1320 */ BlockTessellator* mBlockTessellator;
    /* this + 1328 */ std::byte padding1328[32];
    /* this + 1360 */ ItemRenderer* itemRenderer;
    /* this + 1368 */ GuiData* guiData;
    /* this + 1376 */ std::byte padding1376[1392 - 1376];
    /* this + 1392 */ std::shared_ptr<ToastManager> mToastManager;
    /* this + 1408 */ std::byte padding1408[3232 - 1408];


public:
    // 1.20.71.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2
    ClientInstance(uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9);
    
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2}
    MC void _ClientInstance(uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9);

    /// @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B F1}
    MC int64_t onStartJoinGame(ClientInstance*, int64_t, int64_t, int64_t);

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA}
    MC void requestLeaveGame(bool switchScreen, bool sync);

    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
    void grabMouse();
    void releaseMouse();
    bool isShowingLoadingScreen() const;
    void getRawCameraEntities(WeakEntityRef& outCamera, WeakEntityRef& outCameraTarget) const;

    // 1.21.0.3 - ? - 4C 8B DC 49 89 5B ? 4D 89 4B ? 49 89 53 ? 55 56 57 48 83 EC
    std::shared_ptr<FileDataRequest> getImageFromUrl(const std::string& imageUrl, std::function<void(Bedrock::Http::Status, const Core::Path&, uint64_t)> callback);
    EntityId getCameraEntity() const;
    Actor* getCameraActor() const;
};

static_assert(offsetof(ClientInstance, mLevelRenderer) == 224);
static_assert(offsetof(ClientInstance, mViewportInfo) == 552);
static_assert(sizeof(ClientInstance) == 3232);
