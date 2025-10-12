#include "ModMenuScreen.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/UiEvents.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenEvent.hpp>
#include <mc/src-client/common/client/gui/screens/SceneFactory.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenController.hpp>
#include <mc/src-client/common/client/gui/screens/UIScene.hpp>
#include <mc/src-client/common/client/gui/controls/UIPropertyBag.hpp>

class ModMenuScreenController : public ScreenController {
public:
    ModMenuScreenController(bool useTaskGroup)
        : ScreenController(useTaskGroup) 
    {
        _registerEventHandlers();
    }

    virtual bool canExit() override {
        Log::Info("canExit?");
        return true;
    }

    void _registerEventHandlers() {
        this->registerButtonInteractedHandler(StringToNameId("button.amethyst:close_mods_list"), [this](UIPropertyBag* bag) {
            ClientInstance& ci = *Amethyst::GetClientCtx().mClientInstance;
            SceneFactory& factory = *ci.mSceneFactory;

            // rn it just pops and theres nothing below it... lmao
            factory.getCurrentSceneStack()->schedulePopScreen(1);

            return ui::ViewRequest::None;
        });
    }

    virtual void onInit() override {
        ScreenController::onInit();
        Log::Info("onInit!");
        _test();
    }

    void _test() {
        UIPropertyBag props = UIPropertyBag();
        props.set<std::string>("control_id", "test");
        props.set<std::string>("name", "test_factory");

        Log::Info("Json: {}", props.mJsonValue.toStyledString());

        this->mControlCreateCallback("test_factory", props);
    }
};

void ButtonHandleEvent(UiButtonHandleEvent& ev) {
    if (ev.mScreenEvent.type != ScreenEventType::ButtonEvent) return;
    ButtonScreenEventData& button = ev.mScreenEvent.data.button;

    if (button.id != StringToNameId("button.amethyst:mods") || button.state != ButtonState::Down) return;
    
    ClientInstance& ci = *Amethyst::GetClientCtx().mClientInstance;
    SceneFactory& factory = *ci.mSceneFactory;
    auto controller = std::make_shared<ModMenuScreenController>(true);
    auto scene = factory.createUIScene(*ci.mMinecraftGame, ci, "mod_menu.root_panel", controller);
    auto screen = factory._createScreen(scene);
    factory.getCurrentSceneStack()->pushScreen(screen, true);
    Log::Info("Pushed screen!");
}

void InitModMenuScreen()
{
    auto& bus = Amethyst::GetEventBus();
    bus.AddListener<UiButtonHandleEvent>(ButtonHandleEvent);
}