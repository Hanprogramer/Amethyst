#include "ModMenuScreen.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/UiEvents.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenEvent.hpp>
#include <mc/src-client/common/client/gui/screens/SceneFactory.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenController.hpp>
#include <mc/src-client/common/client/gui/screens/UIScene.hpp>
#include <mc/src-client/common/client/gui/controls/UIPropertyBag.hpp>
#include <amethyst/runtime/mod/ModSettings.hpp>

class ModMenuScreenController : public ScreenController {
public:
	int32_t mSelectedMod;

	ModMenuScreenController(bool useTaskGroup)
		: ScreenController(useTaskGroup), mSelectedMod(0) {
		mSelectedMod = StringToNameId(Amethyst::GetOwnMod()->mInfo->FriendlyName);
		Log::Info("Registering event handlers");
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
			Log::Info("popping");
			// rn it just pops and theres nothing below it... lmao
			//factory.getCurrentSceneStack()->popScreensBackTo(ui::SceneType::StartMenuScene);
			factory.getCurrentSceneStack()->schedulePopScreen(1);

			return ui::ViewRequest::Exit;
		});
	}

	virtual void onEntered() override {
		Log::Info("onEntered");
		_updateContent();
	}

	virtual ui::ViewRequest handleEvent(ScreenEvent& ev) {
		if (ev.type != ScreenEventType::ButtonEvent) return ScreenController::handleEvent(ev);

		ButtonScreenEventData data = ev.data.button;
		if (data.state != ButtonState::Down) return ScreenController::handleEvent(ev);

		auto& mods = Amethyst::GetContext().mModGraph->GetMods();

		auto it = std::find_if(mods.begin(), mods.end(), [&data](const auto& mod) {
			return StringToNameId(mod->FriendlyName) == data.id;
		});

		if (it == mods.end()) return ScreenController::handleEvent(ev);

		mSelectedMod = data.id;
		_updateContent();

		return ui::ViewRequest::ConsumeEvent;
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
			props.set<std::string>("$mod_icon", mod->GetVersionedName());

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
		std::string authorsString = "";
		for (auto& author : modInfo.Authors) {
			authorsString += author + " ";
		}
		UIPropertyBag props = UIPropertyBag();
		props.set<std::string>("control_id", "mod_info_panel");
		props.set<std::string>("$mod_name", modInfo.FriendlyName);
		props.set<std::string>("$mod_version", modInfo.Version.to_string());
		props.set<std::string>("$mod_author", authorsString);
		props.set<std::string>("$mod_icon", modInfo.GetVersionedName());
		this->mControlCreateCallback("mod_info_factory", props);

		// Populate the settings panel (if any)
		auto modPtr = Amethyst::GetContext().mModLoader->GetModByUUID(modInfo.UUID);
		auto mod = modPtr.lock();
		if (mod == nullptr) {
			Log::Info("Failed to lock mod for settings panel");
			return;
		}
		auto& settings = mod->mSettings;


		for (const auto& [key, value] : settings->values) {
			if (settings->HasHint(key)) {
				auto& hint = settings->GetHintFor(key);
				// Specialized UI based on the custom hint
				UIPropertyBag props = UIPropertyBag();
				auto controlid = hint->GetControlId();
				props.set<std::string>("control_id", controlid);
				props.set<std::string>("name", controlid);
				props.set<std::string>("$settings_label", std::format("settings.{}.{}.label", mod->mInfo->Namespace, key));
				hint->PopulateProps(props);
				this->mControlCreateCallback("mod_info_factory", props);
				continue;
			}
			// Primitive default settings UI
			UIPropertyBag props = UIPropertyBag();
			auto controlid = std::format("mod_settings_item_{}", settings->GetValueType(key));
			props.set<std::string>("control_id", controlid);
			props.set<std::string>("name", controlid);
			props.set<std::string>("$settings_label", std::format("settings.{}.{}.label", mod->mInfo->Namespace, key));
			this->mControlCreateCallback("mod_info_factory", props);

		}
		mod.reset();
	}
};

void ButtonHandleEvent(UiButtonHandleEvent& ev) {
	if (ev.mScreenEvent.type != ScreenEventType::ButtonEvent) return;
	ButtonScreenEventData& button = ev.mScreenEvent.data.button;

	if (button.id != StringToNameId("button.amethyst:mods") || button.state != ButtonState::Down) return;

	Amethyst::GetContext().mModLoader->LoadModIcons();

	ClientInstance& ci = *Amethyst::GetClientCtx().mClientInstance;
	SceneFactory& factory = *ci.mSceneFactory;
	auto controller = std::make_shared<ModMenuScreenController>(true);
	auto scene = factory.createUIScene(*ci.mMinecraftGame, ci, "mod_menu.root_panel", controller);
	auto screen = factory._createScreen(scene);
	factory.getCurrentSceneStack()->pushScreen(screen, false);
}

void InitModMenuScreen() {
	auto& bus = Amethyst::GetEventBus();
	bus.AddListener<UiButtonHandleEvent>(ButtonHandleEvent);
}