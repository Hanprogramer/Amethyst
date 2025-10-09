#pragma once
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/runtime/events/EventBus.hpp"
#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/mc/MinecraftPackageInfo.hpp"
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/runtime/mod/ModRepository.hpp"
#include "amethyst/runtime/mod/ModGraph.hpp"
#include "amethyst/runtime/mod/ModLoader.hpp"
#include "amethyst/runtime/patchManager/PatchManager.hpp"
#include "amethyst/runtime/resource/PackManager.hpp"
#include "amethyst/runtime/EnumAllocator.hpp"
#include "amethyst/runtime/platform/Platform.hpp"
#include "amethyst/runtime/networking/NetworkManager.hpp"
#include "mc/src-client/common/client/game/ClientInstance.hpp"
#include "mc/src-client/common/client/input/MinecraftInputHandler.hpp"
#include "mc/src-client/common/client/options/Options.hpp"
#include "mc/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp"
#include "amethyst/Imports.hpp"

class Minecraft;

class AmethystContext {
public:
    // Volatile between mod loads
    std::unique_ptr<Amethyst::HookManager> mHookManager;
    std::unique_ptr<Amethyst::EventBus> mEventBus;
    std::unique_ptr<Amethyst::InputManager> mInputManager;
    std::unique_ptr<Amethyst::PatchManager> mPatchManager;
    std::unique_ptr<Amethyst::EnumAllocator> mEnumAllocator;
    std::unique_ptr<Amethyst::PackManager> mPackManager;
    std::unique_ptr<Amethyst::NetworkManager> mNetworkManager;
    std::unique_ptr<Amethyst::ModRepository> mModRepository;
    std::unique_ptr<Amethyst::ModGraph> mModGraph;
    std::unique_ptr<Amethyst::ModLoader> mModLoader;

    // Non-volatile
    std::unique_ptr<Amethyst::Platform> mPlatform;

    // Threads
    std::thread::id mAmethystThread;
    std::optional<std::thread::id> mMainClientThread;
    std::optional<std::thread::id> mMainServerThread;

    Amethyst::MinecraftPackageInfo mPackageInfo;

    // All of this should probably be moved elsewher
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;
    bool mIsInWorldOrLoading = false;

    Minecraft* mClientMinecraft = nullptr;
    Minecraft* mServerMinecraft = nullptr;

    // prevent copying
    AmethystContext(const AmethystContext&) = delete;
    friend class AmethystRuntime;

protected:
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
    AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread);
};