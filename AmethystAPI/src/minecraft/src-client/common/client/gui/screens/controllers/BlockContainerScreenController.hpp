/// @symbolgeneration
#pragma once
#include "minecraft/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"

class Player;
class BlockPos;
struct ActorUniqueID;
class ContainerManagerController;

/// @vptr {0x4EC2B90}
class BlockContainerScreenController :
	public ContainerScreenController 
{
public:
    std::shared_ptr<ContainerManagerController> mBlockContainerManagerController;

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F1 48 8B FA 48 8B D9 48 89 4C 24}
    MC BlockContainerScreenController(std::shared_ptr<ClientInstanceScreenModel> model, Player& player, const BlockPos& pos, ActorUniqueID actorId);

	/// @vidx {0}
    MC virtual ~BlockContainerScreenController();
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
    /// @vidx {52}
    MC virtual void unknown_52();
    /// @vidx {53}
    MC virtual void unknown_53();
    /// @vidx {54}
    MC virtual void unknown_54();
    /// @vidx {55}
    MC virtual void unknown_55();
    /// @vidx {56}
    MC virtual void unknown_56();
    /// @vidx {57}
    MC virtual void unknown_57();
    /// @vidx {58}
    MC virtual void unknown_58();
    /// @vidx {59}
    MC virtual void unknown_59();
    /// @vidx {60}
    MC virtual void unknown_60();
    /// @vidx {61}
    MC virtual void unknown_61();
    /// @vidx {62}
    MC virtual void unknown_62();
    /// @vidx {63}
    MC virtual void unknown_63();
    /// @vidx {64}
    MC virtual void unknown_64();
    /// @vidx {65}
    MC virtual void unknown_65();
    /// @vidx {66}
    MC virtual void unknown_66();
    /// @vidx {67}
    MC virtual void unknown_67();
    /// @vidx {68}
    MC virtual void unknown_68();
    /// @vidx {69}
    MC virtual void unknown_69();
    /// @vidx {70}
    MC virtual void unknown_70();
    /// @vidx {71}
    MC virtual void unknown_71();
    /// @vidx {72}
    MC virtual void unknown_72();
    /// @vidx {73}
    MC virtual void unknown_73();
    /// @vidx {74}
    MC virtual void unknown_74();
    /// @vidx {75}
    MC virtual void unknown_75();
    /// @vidx {76}
    MC virtual void unknown_76();
};

static_assert(sizeof(BlockContainerScreenController) == 0x1168);