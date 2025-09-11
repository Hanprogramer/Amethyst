#include "hooks/UiHooks.hpp"
#include <amethyst/runtime/events/UiEvents.hpp>
#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"
#include "AmethystRuntime.hpp"
#include <minecraft/src-client/common/client/gui/screens/ScreenEvent.hpp>

SafetyHookInline _ScreenController__handleButtonEvent;

ui::ViewRequest ScreenController__handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
    ui::ViewRequest result = _ScreenController__handleButtonEvent.call<ui::ViewRequest, ScreenController*, ScreenEvent&>(screen, event);

    UiButtonHandleEvent ev(event);
    AmethystRuntime::getEventBus()->Invoke(ev);

    return result;
}

void CreateUiHooks() {
    Amethyst::HookManager* hooks = AmethystRuntime::getHookManager();

    HOOK(ScreenController, _handleButtonEvent);
}