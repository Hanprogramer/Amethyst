#pragma once
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/runtime/events/EventBus.hpp"
#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/mc/MinecraftPackageInfo.hpp"
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/runtime/patchManager/PatchManager.hpp"
#include "amethyst/runtime/resource/PackManager.hpp"
#include "amethyst/runtime/EnumAllocator.hpp"
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
    std::vector<Mod> mMods;

    // Non-volatile
    Amethyst::MinecraftPackageInfo mPackageInfo;
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;
    bool mIsInWorldOrLoading = false;

    Minecraft* mClientMinecraft;
    Minecraft* mServerMinecraft;

    // prevent copying
    AmethystContext(const AmethystContext&) = delete;
    friend class AmethystRuntime;

    const Mod* GetModByNamespace(const std::string& modNamespace) const 
    {
        for (const auto& mod : mMods) {
            if (mod.metadata.modNamespace == modNamespace) {
                return &mod;
            }
        }
        return nullptr;
    }

    Mod* GetModByNamespace(const std::string& modNamespace)
    {
        for (auto& mod : mMods) {
            if (mod.metadata.modNamespace == modNamespace) {
                return &mod;
            }
        }
        return nullptr;
    }

protected:
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
    AmethystContext() = default;
};