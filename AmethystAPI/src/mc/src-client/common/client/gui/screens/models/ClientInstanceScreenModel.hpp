/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src-client/common/client/gui/screens/models/MinecraftScreenModel.hpp"

enum class UIProfile : int {
    Classic = 0x0000,
    Pocket = 0x0001
};

/// @vptr {0x4CB1C48}
class ClientInstanceScreenModel : 
	public MinecraftScreenModel 
{
public:
    MC static uintptr_t $vtable_for_this;

    std::byte padding332[0x128 - sizeof(MinecraftScreenModel)]; // full_size - base

    /// @signature {48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B D9 48 89 4C 24 ? 48 89 54 24 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B D0 48 8B CB E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 03 48 8D 8B}
    MC ClientInstanceScreenModel(const MinecraftScreenModel::Context& context);

    /// @vidx {0}
    MC virtual ~ClientInstanceScreenModel();
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

    /// @signature {48 89 5C 24 ? 57 48 83 EC ? 48 8B D1 48 8B 41 ? 48 85 C0 74 ? 48 83 38 ? 74 ? 48 8B 41 ? 48 85 C0 74 ? F0 FF 40 ? 48 8B 49 ? 48 89 4C 24 ? 48 8B 5A ? 48 89 5C 24 ? 48 8B 09 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 8B C8 48 8B 82 ? ? ? ? FF 15 ? ? ? ? 8B F8 48 85 DB 74 ? 48 8B CB E8 ? ? ? ? 8B C7 48 8B 5C 24 ? 48 83 C4 ? 5F C3 E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 55}
    MC UIProfile getUIProfile();
};