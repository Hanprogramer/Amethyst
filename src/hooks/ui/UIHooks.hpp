#pragma once
#include "loader/AmethystRuntime.hpp"
#include "loader/AmethystRuntime.hpp"
#include "amethyst/runtime/events/UiEvents.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/utility/InlineHook.hpp"
#include "mc/src-client/common/client/gui/screens/ScreenController.hpp"
#include "mc/src-client/common/client/gui/screens/ScreenEvent.hpp"
#include "mc/src-client/common/client/gui/screens/controllers/StartMenuScreenController.hpp"
#include "mc/src-deps/core/string/StringHash.hpp"

namespace Amethyst::UIHooks {
namespace ScreenControllerHooks {
inline Amethyst::InlineHook<decltype(&ScreenController::_handleButtonEvent)> __handleButtonEvent;

ui::ViewRequest _handleButtonEvent(ScreenController* self, ScreenEvent& event);
}

namespace StartMenuScreenControllerHooks {
inline Amethyst::InlineHook<decltype(&StartMenuScreenController::_registerBindings)> __registerBindings;

void _registerBindings(StartMenuScreenController* self);
}

void Create();
}