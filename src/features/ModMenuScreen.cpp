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
    int32_t mSelectedMod;

    ModMenuScreenController(bool useTaskGroup)
        : ScreenController(useTaskGroup), mSelectedMod(0)
    {
        mSelectedMod = StringToNameId(Amethyst::GetOwnMod()->mInfo->FriendlyName);
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
        Log::Info("ev: {}", (uint64_t)ev.type);

        switch (ev.type) {
            case ScreenEventType::ToggleChangeEvent: {
                _handleToggle(ev.data.toggle);
                return ui::ViewRequest::ConsumeEvent;
            }
            case ScreenEventType::SliderChangeEvent: {
                _handleSlider(ev.data.slider);
                return ui::ViewRequest::ConsumeEvent;
            }
        }
        
        if (ev.type != ScreenEventType::ButtonEvent) return ui::ViewRequest::None;

        ButtonScreenEventData data = ev.data.button;
        if (data.state != ButtonState::Down) return ui::ViewRequest::None;

        auto& mods = Amethyst::GetContext().mModGraph->GetMods();

        auto it = std::find_if(mods.begin(), mods.end(), [&data](const auto& mod) {
            return StringToNameId(mod->FriendlyName) == data.id;
        });

        if (it == mods.end()) return ui::ViewRequest::None;

        mSelectedMod = data.id;

        Log::Info("props: {}", ev.data.button.properties->mJsonValue.toStyledString());
        _updateContent();

        return ui::ViewRequest::Refresh;
    }

private:
    void _handleToggle(ToggleChangeEventData& toggle) {
        Log::Info("{} {} {} {}", toggle.index, toggle.id, toggle.state, toggle.properties->mJsonValue.toStyledString());
    }

    void _handleSlider(SliderChangeEventData& slider)
    {
        Log::Info("{} {} {}", slider.index, slider.id, slider.properties->mJsonValue.toStyledString());
    }

    void _updateContent() {
        auto& mods = Amethyst::GetContext().mModGraph->GetMods();
        this->mControlDestroyAllCallback("mods_list_factory");

        // Populate left side mod list
        for (auto& mod : mods) {
            UIPropertyBag props = UIPropertyBag();
            props.set<std::string>("control_id", "mod_list_item");
            props.set<std::string>("name", "mod_list_item");
            props.set<std::string>("$mod_name", mod->FriendlyName);

            this->mControlCreateCallback("mods_list_factory", props);
        }

        this->mControlDestroyAllCallback("mod_info_factory");

        auto it = std::find_if(mods.begin(), mods.end(), [this](const auto& mod) {
            return StringToNameId(mod->FriendlyName) == mSelectedMod;
        });

        if (it == mods.end()) {
            Log::Info("Failed to find current mod?");
            return;
        }

        const Amethyst::ModInfo& modInfo = *it->get();

        // Populate mod info
        UIPropertyBag props = UIPropertyBag();
        props.set<std::string>("control_id", "mod_name");
        props.set<std::string>("$mod_name", modInfo.FriendlyName);
        this->mControlCreateCallback("mod_info_factory", props);

        UIPropertyBag toggleProps = UIPropertyBag();
        toggleProps.set<std::string>("control_id", "toggle");
        toggleProps.set<std::string>("$option_label", "Test Label");
        toggleProps.set<std::string>("$option_binding_name", "#test_binding");
        toggleProps.set<std::string>("$toggle_name", "Toggle Name");
        this->mControlCreateCallback("mod_info_factory", toggleProps);

        UIPropertyBag sliderProps = UIPropertyBag();
        sliderProps.set<std::string>("control_id", "slider");
        sliderProps.set<std::string>("$option_label", "Test Label");
        sliderProps.set<std::string>("$slider_name", "Slider Name");
        sliderProps.set<std::string>("$slider_value_binding_name", "#fake_binding");
        this->mControlCreateCallback("mod_info_factory", sliderProps);
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
}

void InitModMenuScreen()
{
    auto& bus = Amethyst::GetEventBus();
    bus.AddListener<UiButtonHandleEvent>(ButtonHandleEvent);
}