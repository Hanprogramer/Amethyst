#include "hooks/ui/UIHooks.hpp"

ui::ViewRequest Amethyst::UIHooks::ScreenControllerHooks::_handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
    ui::ViewRequest result = __handleButtonEvent(screen, event);
    UIButtonHandleEvent ev(event);
    Amethyst::GetEventBus().Invoke(ev);
    return result;
}

void Amethyst::UIHooks::StartMenuScreenControllerHooks::_registerBindings(StartMenuScreenController* self)
{
    __registerBindings(self);

    auto& context = Amethyst::GetContext();
    const Amethyst::Mod* ownMod = Amethyst::GetOwnMod();
    std::string versionStr;
    if (ownMod->mInfo->Version.prerelease_tag() == "dev")
        versionStr = std::format("{}", "§uAmethyst Runtime (DEV)§r");
    else
        versionStr = std::format("Amethyst Runtime v{}", ownMod->mInfo->Version.to_string());

    // Register '#amethyst_version' binding
    self->bindString(StringHash("#amethyst_version"), [versionStr]() { 
        return versionStr;
    }, []() { 
        return true; 
    });

    // Register '#mods_loaded' binding
    self->bindString(StringHash("#mods_loaded"), [&context]() { 
        size_t count = 0;
        if (context.mModLoader) {
            count = context.mModLoader->GetModCount();
        }
        return std::format("Mods Loaded: {}", count); 
    }, []() { 
        return true; 
    });
}

void Amethyst::UIHooks::Create() {
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    hooks.CreateDirectHook<&ScreenController::_handleButtonEvent>(ScreenControllerHooks::__handleButtonEvent, &ScreenControllerHooks::_handleButtonEvent);
    hooks.CreateDirectHook<&StartMenuScreenController::_registerBindings>(StartMenuScreenControllerHooks::__registerBindings, &StartMenuScreenControllerHooks::_registerBindings);
}