#include "hooks/ui/UIHooks.hpp"
#include "AmethystRuntime.hpp"
#include <amethyst/runtime/events/UiEvents.hpp>
#include <amethyst/Log.hpp>

#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"
#include "minecraft/src-client/common/client/gui/screens/ScreenEvent.hpp"
#include "minecraft/src-client/common/client/gui/screens/controllers/StartMenuScreenController.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"

SafetyHookInline _ScreenController__handleButtonEvent;
SafetyHookInline _StartMenuScreenController__registerBindings;

ui::ViewRequest ScreenController__handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
    ui::ViewRequest result = _ScreenController__handleButtonEvent.call<ui::ViewRequest, ScreenController*, ScreenEvent&>(screen, event);

    UIButtonHandleEvent ev(event);
    AmethystRuntime::getEventBus()->Invoke(ev);

    return result;
}

void StartMenuScreenController__registerBindings(StartMenuScreenController* self)
{
    _StartMenuScreenController__registerBindings.call(self);
    auto& context = *AmethystRuntime::getContext();

    // Register '#amethyst_version' binding
    self->bindString({StringToNameId("#amethyst_version")}, []() { return std::format("Amethyst Runtime v{}", MOD_VERSION); }, []() { return true; });

    // Register '#mods_loaded' binding
    self->bindString({StringToNameId("#mods_loaded")}, [&context]() { return std::format("Mods Loaded: {}", context.mModLoader->GetModCount()); }, []() { return true; });
}



void CreateUIHooks() {
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();
    HOOK(ScreenController, _handleButtonEvent);
}

void CreateStartScreenHooks()
{
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();
    HOOK(StartMenuScreenController, _registerBindings);
}