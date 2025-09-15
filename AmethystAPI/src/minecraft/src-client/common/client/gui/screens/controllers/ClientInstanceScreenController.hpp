/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src-client/common/client/gui/screens/controllers/MinecraftScreenController.hpp"
#include "minecraft/src-client/common/client/gui/screens/models/ClientInstanceScreenModel.hpp"

class PlatformMultiplayerRestrictions;

/// @vptr {0x4CC91C0}
class ClientInstanceScreenController :
	public MinecraftScreenController
{
public:
    std::shared_ptr<ClientInstanceScreenModel> mClientInstanceScreenModel;
    std::unique_ptr<PlatformMultiplayerRestrictions> mPlatformMultiplayerRestrictions;

	/// @signature {48 89 5C 24 ? 48 89 54 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 0F 57 C0 F3 0F 7F 44 24 ? 48 8B 42 ? 48 85 C0 74 ? F0 FF 40 ? 48 8B 02 48 89 44 24 ? 48 8B 42 ? 48 89 44 24 ? 41 B1 ? 45 33 C0 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 03 48 8D 05 ? ? ? ? 48 89 83 ? ? ? ? 33 C0}
    MC ClientInstanceScreenController(std::shared_ptr<ClientInstanceScreenModel> model);

    /// @vidx {0}
    MC virtual ~ClientInstanceScreenController();
    /// @vidx {1}
    MC virtual void preFrameTick();
    /// @vidx {2}
    MC virtual ui::DirtyFlag tick();
    /// @vidx {3}
    MC virtual ui::ViewRequest handleEvent(ScreenEvent& event);
    /// @vidx {4}
    MC virtual std::optional<std::string> getRoute();
    /// @vidx {5}
    MC virtual void setScreenState(const std::vector<std::pair<std::string_view, std::string_view>>& state);
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
    /// @vidx {14}
    MC virtual void unknown_14();
    /// @vidx {15}
    MC virtual void unknown_15();
    /// @vidx {16}
    MC virtual void unknown_16();
    /// @vidx {17}
    MC virtual void unknown_17();
    /// @vidx {18}
    MC virtual void unknown_18();
    /// @vidx {19}
    MC virtual void unknown_19();
    /// @vidx {20}
    MC virtual void unknown_20();
    /// @vidx {21}
    MC virtual void unknown_21();
    /// @vidx {22}
    MC virtual void unknown_22();
    /// @vidx {23}
    MC virtual void unknown_23();
    /// @vidx {24}
    MC virtual void unknown_24();
    /// @vidx {25}
    MC virtual void unknown_25();
    /// @vidx {26}
    MC virtual void unknown_26();
    /// @vidx {27}
    MC virtual void unknown_27();
    /// @vidx {28}
    MC virtual void unknown_28();
    /// @vidx {29}
    MC virtual void unknown_29();
    /// @vidx {30}
    MC virtual void unknown_30();
    /// @vidx {31}
    MC virtual void unknown_31();
    /// @vidx {32}
    MC virtual void unknown_32();
    /// @vidx {33}
    MC virtual void unknown_33();
    /// @vidx {34}
    MC virtual void unknown_34();
    /// @vidx {35}
    MC virtual void unknown_35();
    /// @vidx {36}
    MC virtual void unknown_36();
    /// @vidx {37}
    MC virtual void unknown_37();
    /// @vidx {38}
    MC virtual void unknown_38();
    /// @vidx {39}
    MC virtual void unknown_39();
    /// @vidx {40}
    MC virtual void unknown_40();
    /// @vidx {41}
    MC virtual void unknown_41();
    /// @vidx {42}
    MC virtual void unknown_42();
    /// @vidx {43}
    MC virtual void unknown_43();
    /// @vidx {44}
    MC virtual void unknown_44();
    /// @vidx {45}
    MC virtual void unknown_45();
    /// @vidx {46}
    MC virtual void unknown_46();
    /// @vidx {47}
    MC virtual void unknown_47();
    /// @vidx {48}
    MC virtual void unknown_48();
    /// @vidx {49}
    MC virtual void unknown_49();
    /// @vidx {50}
    MC virtual void unknown_50();
    /// @vidx {51}
    MC virtual void unknown_51();
};

static_assert(sizeof(ClientInstanceScreenController) == 0xC38);