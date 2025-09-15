/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src/common/config/ScreenCapabilities.hpp"
#include "minecraft/src-client/common/client/game/MinecraftGame.hpp"
#include "minecraft/src-client/common/client/game/IClientInstance.hpp"

class SceneStack;
class IAdvancedGraphicsOptions;

/// @vptr {0x4D01468}
class MinecraftScreenModel : 
    public std::enable_shared_from_this<MinecraftScreenModel> 
{
public:
    class Context {
    public:
        MinecraftGame& mMinecraft;
        ClientInstance& mClient;
        Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions> mAdvancedGraphicsOptions;
        Bedrock::NotNullNonOwnerPtr<SceneStack> mSceneStack;
        SceneFactory& mSceneFactory;
        std::unique_ptr<IScreenCapabilities> mCapabilities;
    };

    MC static uintptr_t $vtable_for_this;
    std::byte padding24[0xE8 - 0x10 - 0x8]; // full_size - shared_from_this - vptr

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B F2 48 8B F1 48 89 4D ? 48 89 55 ? 33 D2}
    MC MinecraftScreenModel(const MinecraftScreenModel::Context& context);

    /// @vidx {0}
    MC virtual ~MinecraftScreenModel();
    /// @vidx {1}
    MC virtual void unknown_1();
    /// @vidx {2}
    MC virtual void unknown_2();
    /// @vidx {3}
    MC virtual void unknown_3();
    /// @vidx {4}
    MC virtual void unknown_4();
    /// @vidx {5}
    MC virtual void unknown_5();
    /// @vidx {6}
    MC virtual void unknown_6();
    /// @vidx {7}
    MC virtual void unknown_7();
    /// @vidx {8}
    MC virtual void unknown_8();
    /// @vidx {9}
    MC virtual void unknown_9();
    /// @vidx {10}
    MC virtual void unknown_10();
    /// @vidx {11}
    MC virtual void unknown_11();
    /// @vidx {12}
    MC virtual void unknown_12();
    /// @vidx {13}
    MC virtual void unknown_13();
};