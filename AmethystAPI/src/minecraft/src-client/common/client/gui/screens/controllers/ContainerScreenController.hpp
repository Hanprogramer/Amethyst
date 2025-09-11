/// @symbolgeneration
#pragma once
#include <unordered_map>
#include <string>
#include <amethyst/ModApi.hpp>
#include "minecraft/src/common/world/containers/ContainerEnumName.hpp"


#pragma pack(push, 1)
class ContainerScreenController /** : ClientInstanceScreenController, MinecraftScreenController, ScreenController, IScreenController, std::enable_shared_from_this<MinecraftScreenController> **/ {
public:
    /// @address {0x59D9150}
    MC static std::unordered_map<ContainerEnumName, std::string> ContainerCollectionNameMap;
};
#pragma pack(pop)
