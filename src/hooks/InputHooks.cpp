#include "hooks/InputHooks.hpp"
#include <amethyst/runtime/events/InputEvents.hpp>
#include <minecraft/src-deps/input/MouseDevice.hpp>
#include <amethyst/Log.hpp>

SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline _VanillaClientInputMappingFactory_createInputMappingTemplates;
SafetyHookInline _MouseDevice_feed;
SafetyHookInline _InputHandler_handleButtonEvent;

void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    _addFullKeyboardGamePlayControls.call(self, keyboard, mouse);

    Amethyst::InputManager* inputManager = AmethystRuntime::getInputManager();
    inputManager->_registerKeyboardInputs(self, keyboard, mouse, Amethyst::KeybindContext::Gameplay);
}

void VanillaClientInputMappingFactory_createInputMappingTemplates(VanillaClientInputMappingFactory* self, Options* opt) {
    _VanillaClientInputMappingFactory_createInputMappingTemplates.call(self, opt);

    // This options is cached for later times the runtime needs to add keybinds.
    // This function createInputMappingTemplates is called once at the very start of the game and never again.
    AmethystRuntime::getContext()->mOptions = opt;

    // Since this is the first time, register all custom keybinds now that options is available.
    RegisterInputsEvent event(*AmethystRuntime::getInputManager());
    AmethystRuntime::getEventBus()->Invoke(event);
}

void MouseDevice_feed(MouseDevice* mouse, char actionButtonId, char buttonData, short x, short y, short dx, short dy, bool forceMotionlessPointer) {
    MouseInputEvent event(actionButtonId, buttonData, x, y, dx, dy);
    AmethystRuntime::getEventBus()->Invoke(event);

    if (!event.IsCanceled()) {
        _MouseDevice_feed.thiscall(mouse, actionButtonId, buttonData, x, y, dx, dy, forceMotionlessPointer);
    }
}

void InputHandler_handleButtonEvent(InputHandler* self, const ButtonEventData& button, FocusImpact focus, IClientInstance& client, int controllerId)
{
    Amethyst::InputPassthrough passthrough = AmethystRuntime::getInputManager()->_handleButtonEvent(self, button, focus, client, controllerId);

    if (passthrough == Amethyst::InputPassthrough::Passthrough) {
        _InputHandler_handleButtonEvent.call<void, InputHandler*, const ButtonEventData&, FocusImpact, IClientInstance&, int>(self, button, focus, client, controllerId);
    }
}

void CreateInputHooks()
{
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();
    Amethyst::RuntimeImporter& importer = *AmethystRuntime::getRuntimeImporter();

    hooks.CreateVirtualHook<&VanillaClientInputMappingFactory::createInputMappingTemplates>(
        importer.GetVirtualTableAddress("VanillaClientInputMappingFactory::vtable::'this'"),
        _VanillaClientInputMappingFactory_createInputMappingTemplates,
        VanillaClientInputMappingFactory_createInputMappingTemplates
    );

    hooks.CreateDirectHook<&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls>(_addFullKeyboardGamePlayControls, &addFullKeyboardGamePlayControls);
    hooks.CreateDirectHook<&MouseDevice::feed>(_MouseDevice_feed, &MouseDevice_feed);
    hooks.CreateDirectHook<&InputHandler::handleButtonEvent>(_InputHandler_handleButtonEvent, &InputHandler_handleButtonEvent);
}