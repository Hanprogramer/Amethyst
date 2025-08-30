#pragma once
#include <memory>
#include <minecraft/src-client/common/client/renderer/TextureGroup.hpp>
#include <minecraft/src-client/common/client/gui/gui/FontHandle.hpp>

// class MinecraftGame : public BedrockEngine::AppIsland, App, IMinecraftGame, LevelListener,
//                             ResourcePackListener, OptionsObserver, ActiveDirectoryIdentityObserver

class MinecraftInputHandler;
class FontRepository;

class MinecraftGame {
public:
    /* this + 0    */ uintptr_t** vtable;
    /* this + 8    */ std::byte padding8[352 - 8];
    /* this + 352  */ std::shared_ptr<FontRepository> mFontRepository; 
    /* this + 368  */ std::byte padding368[1920 - 368];
    /* this + 1920 */ std::shared_ptr<mce::TextureGroup> mTextures;
    /* this + 1936 */ std::byte padding1936[3328 - 1936];
    /* this + 3328 */ std::unique_ptr<MinecraftInputHandler> mInput;
    /* this + 3336 */ std::byte padding3336[3912 - 3336];
    /* this + 3912 */ FontHandle mFontHandle;
    /* this + 3984 */ FontHandle mRuneFontHandle;
    /* this + 4056 */ FontHandle mUnicodeFontHandle;
    /* this + 4128 */ FontHandle mSmoothFontLatinHandle;
    /* this + 4200 */ FontHandle mUIFontHandle;
};

// 1.21.0.3
static_assert(offsetof(MinecraftGame, mTextures) == 1920);