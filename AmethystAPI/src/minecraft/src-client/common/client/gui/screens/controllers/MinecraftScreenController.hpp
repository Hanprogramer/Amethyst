/// @symbolgeneration
#pragma once
#include <memory>
#include "amethyst/Imports.hpp"
#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"

enum class ScreenExitBehavior : int {
    LeaveScreen = 0x0000,
    ExitGame = 0x0001,
    GoToStartScreen = 0x0002,
    DoNothing = 0x0003
};

enum class HoloUIInputMode : uint32_t {
    Unknown = 0x0000,
    Controller = 0x0001,
    Gaze = 0x0002,
    Mouse = 0x0003
};

class MinecraftScreenModel;

/// @vptr {0x4D03830}
class MinecraftScreenController :
	public ScreenController,
	public Bedrock::EnableNonOwnerReferences,
    public std ::enable_shared_from_this<MinecraftScreenController> 
{
public:
    struct LeaveScreenInfo {
        std::byte padding0[0x28];
    };

    std::shared_ptr<MinecraftScreenModel> mMinecraftScreenModel;
    ScreenExitBehavior mExitBehavior;
    InputMode mInputMode;
    HoloUIInputMode mHoloUIInputMode;
    InputMode mPreviousInputMode;
    HoloUIInputMode mPreviousHoloUIInputMode;
    bool mPlayerDied;
    std::function<void __cdecl(enum ModalScreenButtonId)> mModalDialogResultCallback;
    std::string mTTSTitle;
    std::string mTTSDialogMessage;
    MinecraftScreenController::LeaveScreenInfo mLeaveScreen;
    bool mRayTracingActive;
    std::unordered_map<std::string, std::vector<bool>> mDropDownActive;
    std::unordered_map<std::string, int> mStepSliderValues;
    bool mIsShowErrorScreenInProgress;

    /// @signature {48 89 5C 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 41 0F B6 E9 41 8B F8}
    MC MinecraftScreenController(std::shared_ptr<MinecraftScreenModel> model, ScreenExitBehavior exitBehavior, bool flag);

    /// @vidx {0}
    MC virtual ~MinecraftScreenController();
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

static_assert(sizeof(MinecraftScreenController) == 0xC20);