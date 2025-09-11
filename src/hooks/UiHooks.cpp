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
    Amethyst::HookManager* hookManager = AmethystRuntime::getHookManager();

    NO_THROW_HOOK(ScreenController, _handleButtonEvent, "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 10 52");
}