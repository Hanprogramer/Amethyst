#pragma once
#include "loader/AmethystRuntime.hpp"
#include <mc/src-client/common/client/game/ClientInstance.hpp>
#include <mc/src-client/common/client/input/ClientInputHandler.hpp>
#include <mc/src-client/common/client/input/MinecraftInputHandler.hpp>
#include <mc/src-client/common/client/input/RemappingLayout.hpp>
#include <mc/src-client/common/client/input/VanillaClientInputMappingFactory.hpp>
#include <mc/src-client/common/client/options/Options.hpp>

void CreateInputHooks();