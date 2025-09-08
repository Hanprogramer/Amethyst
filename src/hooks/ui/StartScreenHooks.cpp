#include "hooks/ui/StartScreenHooks.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"
#include "minecraft/src-client/common/client/gui/screens/controllers/StartMenuScreenController.hpp"
#include "amethyst/Log.hpp"

SafetyHookInline _StartMenuScreenController__registerBindings;
void StartMenuScreenController__registerBindings(StartMenuScreenController* self) {
    _StartMenuScreenController__registerBindings.call(self);
    auto& context = *AmethystRuntime::getContext();

    // Register '#amethyst_version' binding
    self->bindString({ StringToNameId("#amethyst_version") }, []() { return std::format("Amethyst Runtime v{}", MOD_VERSION); }, []() { return true; });

    // Register '#mods_loaded' binding
    self->bindString({ StringToNameId("#mods_loaded") }, [&context]() { return std::format("Mods Loaded: {}", context.mMods.size()); }, []() { return true; });
}

void CreateStartScreenHooks() {
    auto& hooks = *AmethystRuntime::getHookManager();

    hooks.RegisterFunction<&StartMenuScreenController::_registerBindings>();
    hooks.CreateHook<&StartMenuScreenController::_registerBindings>(_StartMenuScreenController__registerBindings, &StartMenuScreenController__registerBindings);
}