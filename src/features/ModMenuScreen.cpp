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
    bool mDirty;
    std::unordered_map<uint32_t, std::string> mModNameHashToName;

    ModMenuScreenController(bool useTaskGroup)
        : ScreenController(useTaskGroup), mDirty(true)
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

    virtual void onEntered() override {
        Log::Info("onEntered");
        _updateContent();
    }

    virtual ui::ViewRequest handleEvent(ScreenEvent& ev) {
        if (ev.type != ScreenEventType::ButtonEvent) return ui::ViewRequest::None;

        ButtonScreenEventData data = ev.data.button;
        if (data.state != ButtonState::Down) return ui::ViewRequest::None;

        Log::Info("buttonId: {}", data.fromButtonId);

        auto it = mModNameHashToName.find(data.fromButtonId);
        if (it == mModNameHashToName.end()) {
            Log::Info("Failed to find clicked mod?");
            return ui::ViewRequest::None;
        }

        Log::Info("Pressed: {}", it->second);

        return ui::ViewRequest::ConsumeEvent;
    }

    void _updateContent() {
        auto& mods = Amethyst::GetContext().mModGraph->GetMods();
        mModNameHashToName.clear();

        for (auto& mod : mods) {
            UIPropertyBag props = UIPropertyBag();
            props.set<std::string>("control_id", "mod_list_item");
            props.set<std::string>("name", "mod_list_item");
            props.set<std::string>("$mod_name", mod->FriendlyName);

            mModNameHashToName.emplace(StringToNameId(mod->FriendlyName), mod->FriendlyName);

            this->mControlCreateCallback("mods_list_factory", props);
        }

        this->mDirty = false;
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