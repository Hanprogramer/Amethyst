#include "hooks/ui/UIHooks.hpp"
#include "mc/src/common/locale/I18n.hpp"

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
    self->bindString(StringHash("#mods_loaded"), [&context]() -> std::string { 
        if (reinterpret_cast<uintptr_t>(&getI18n) == reinterpret_cast<uintptr_t>(&Amethyst::RuntimeImporter::UninitializedFunctionHandler) || !context.mModLoader) {
            return "No mods loaded";
        }
        size_t count = context.mModLoader->GetModCount();
        std::string modsLoadedLocalized = "text.amethyst.mods_loaded"_i18n;
        bool plural = (count != 1);
        std::string pluralSuffix = plural ? "s" : "";
        return std::vformat(modsLoadedLocalized, std::make_format_args(count, pluralSuffix, pluralSuffix));
    }, []() { 
        return true; 
    });
}

void Amethyst::UIHooks::Create() {
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    hooks.CreateDirectHook<&ScreenController::_handleButtonEvent>(ScreenControllerHooks::__handleButtonEvent, &ScreenControllerHooks::_handleButtonEvent);
    hooks.CreateDirectHook<&StartMenuScreenController::_registerBindings>(StartMenuScreenControllerHooks::__registerBindings, &StartMenuScreenControllerHooks::_registerBindings);
}