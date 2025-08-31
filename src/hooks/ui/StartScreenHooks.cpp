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

    hooks.RegisterFunction<&StartMenuScreenController::_registerBindings>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B D9 48 8B 81");
    hooks.CreateHook<&StartMenuScreenController::_registerBindings>(_StartMenuScreenController__registerBindings, &StartMenuScreenController__registerBindings);
}