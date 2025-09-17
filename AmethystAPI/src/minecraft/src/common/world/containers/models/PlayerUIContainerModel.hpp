#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src/common/world/containers/models/ContainerModel.hpp"

enum class ContainerEnumName;
class Player;

class PlayerUIContainerModel : 
    public ContainerModel 
{
public:
    MC PlayerUIContainerModel(ContainerEnumName, Player&);
};