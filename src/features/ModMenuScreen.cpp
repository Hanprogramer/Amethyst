#include "ModMenuScreen.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/mod/Mod.hpp>
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

			// Save mod settings
			for (const auto& modPtr : Amethyst::GetContext().mModLoader->GetMods()) {
				auto mod = modPtr.lock();
				mod->SaveSettings();
				mod.reset();
			}

			factory.getCurrentSceneStack()->schedulePopScreen(1);
			return ui::ViewRequest::Exit;
		});
	}

	virtual void onEntered() override {
		_updateContent();
	}

	bool setEnumOptionVisible(std::string settings_name, std::string settings_mod, std::string settings_key, bool value) {
		auto& mods = Amethyst::GetContext().mModGraph->GetMods();
		// Try to find the corresponding mod
		auto it = std::find_if(mods.begin(), mods.end(), [&settings_mod](const auto& mod) {
			return mod->Namespace == settings_mod;
		});
		if (it == mods.end()) return false;

		// Find the settings hint based on it
		auto modInfo = it->get();
		auto modPtr = Amethyst::GetContext().mModLoader->GetModByUUID(modInfo->UUID);
		auto mod = modPtr.lock();
		if (mod == nullptr) {
			Log::Info("Failed to lock mod for dropdown state change: {}", settings_mod);
			return false;
		}

		// Set the state to false then refresh the UI
		auto& settings = mod->mSettings;
		auto ptr = settings->GetHintFor(settings_key);
		if (!ptr) {
			Log::Error("Couldn't find settings hint for {}:{}", settings_mod, settings_key);
			return false;
		}
		if (auto hint = std::dynamic_pointer_cast<Amethyst::EnumOptionsSettingsHint>(ptr)) {
			hint->opened = value;
			return true;
		}

		Log::Error("Couldn't cast settings hint for {}:{}", settings_mod, settings_key);
		return false;
	}

	virtual ui::ViewRequest handleEvent(ScreenEvent& ev) {
		if (ev.type == ScreenEventType::ButtonEvent) {
			ButtonScreenEventData data = ev.data.button;
			if (data.state != ButtonState::Down) return ScreenController::handleEvent(ev);

			auto& mods = Amethyst::GetContext().mModGraph->GetMods();

			if (data.id == StringToNameId("button.dropdown_exit")) {
				// Close the dropdown
				std::string settings_name = ev.data.toggle.properties->mJsonValue.get("$settings_namespaced_id", "").asString();
				std::string settings_mod = ev.data.toggle.properties->mJsonValue.get("$settings_namespace", "").asString();
				std::string settings_id = data.properties->mJsonValue["$settings_id"].asString();
				if (settings_name.empty() || settings_mod.empty() || settings_id.empty()) {
					Log::Error("Dropdown close event missing settings info: $settings_namespaced_id, $settings_namespace, $settings_id");
					return ScreenController::handleEvent(ev);
				}
				if (setEnumOptionVisible(settings_name, settings_mod, settings_id, false)) {
					Log::Info("Closed");
					return ui::ViewRequest::Refresh;
				}
			}

			auto it = std::find_if(mods.begin(), mods.end(), [&data](const auto& mod) {
				return StringToNameId(mod->FriendlyName) == data.id;
			});

			if (it == mods.end()) return ScreenController::handleEvent(ev);

			mSelectedMod = data.id;
			_updateContent();
			//return ui::ViewRequest::ConsumeEvent;
			return ScreenController::handleEvent(ev);
		} else if (ev.type == ScreenEventType::TextEditChange) {
			auto& data = ev.data.textEdit;
			if (data.id == StringToNameId("textedit.amethyst:mod_setting_string")) {
				std::string newText = data.properties->mJsonValue["#item_name"].asString();
				std::string settings_namespace = data.properties->mJsonValue["$settings_namespace"].asString();
				std::string settings_id = data.properties->mJsonValue["$settings_id"].asString();
				auto modPtr = Amethyst::GetContext().mModLoader->GetModByNamespace(settings_namespace);
				auto mod = modPtr.lock();
				if (mod == nullptr) {
					Log::Info("Failed to lock mod for text edit: {}", settings_namespace);
					return ScreenController::handleEvent(ev);
				}
				auto& settings = mod->mSettings;
				settings->PutString(settings_id, newText);
				mod.reset();
			} else if (data.id == StringToNameId("textedit.amethyst:mod_setting_int")) {
				std::string newText = data.properties->mJsonValue["#item_name"].asString();
				if (newText.empty())
					newText = "-1";
				try {
					int v = std::stoi(newText); // throws std::invalid_argument or std::out_of_range
					std::string settings_namespace = data.properties->mJsonValue["$settings_namespace"].asString();
					std::string settings_id = data.properties->mJsonValue["$settings_id"].asString();
					auto modPtr = Amethyst::GetContext().mModLoader->GetModByNamespace(settings_namespace);
					auto mod = modPtr.lock();
					if (mod == nullptr) {
						Log::Info("Failed to lock mod for text edit: {}", settings_namespace);
						return ScreenController::handleEvent(ev);
					}
					auto& settings = mod->mSettings;
					settings->PutInt(settings_id, v);
					mod.reset();
				} catch (const std::invalid_argument&) {
					// not a number
					Log::Error("Value inserted not a number: {}", newText);
				} catch (const std::out_of_range&) {
					// number too large
					Log::Error("Value inserted out of range: {}", newText);
				}
			}
		} else if (ev.type == ScreenEventType::ToggleChangeEvent) {
			// Close the dropdown
			std::string settings_name = ev.data.toggle.properties->mJsonValue.get("$settings_namespaced_id", "").asString();
			std::string settings_mod = ev.data.toggle.properties->mJsonValue.get("$settings_namespace", "").asString();
			std::string settings_id = ev.data.toggle.properties->mJsonValue["$settings_id"].asString();
			auto val = ev.data.toggle.state;

			if (settings_name.empty() || settings_mod.empty() || settings_id.empty()) {
				Log::Error("Dropdown event missing settings info: $settings_namespaced_id, $settings_namespace, $settings_id");
				return ScreenController::handleEvent(ev);
			}
			if (setEnumOptionVisible(settings_name, settings_mod, settings_id, val)) {
				Log::Info("Opened?: {}", val);
				return ui::ViewRequest::Refresh;
			}
		}

		return ScreenController::handleEvent(ev);
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
			UIPropertyBag props = UIPropertyBag();
			auto controlid = std::format("mod_settings_item_{}", settings->GetValueType(key));
			auto controlname = std::format("{}_{}_{}", controlid, mod->mInfo->Namespace, key);
			if (settings->HasHint(key)) {
				auto hint = settings->GetHintFor(key);
				if (!hint) continue;
				// Specialized UI based on the custom hint
				controlid = hint->GetControlId(mod->mInfo->Namespace, key);
				hint->PopulateProps(this, controlid, controlname, settings, mod->mInfo->Namespace, key, props);
			}

			// Primitive default settings UI
			props.set<std::string>("control_id", controlid);
			props.set<std::string>("name", controlname);
			props.set<std::string>("$settings_label", std::format("settings.{}.{}.label", mod->mInfo->Namespace, key));
			props.set<std::string>("$settings_namespace", mod->mInfo->Namespace);
			props.set<std::string>("$settings_id", key);
			props.set<std::string>("$settings_namespaced_id", std::format("{}:{}", mod->mInfo->Namespace, key));
			props.set<std::string>("$settings_control_name", controlname);

			auto type = settings->GetValueType(key);
			if (type == "bool") {
				props.set<bool>("$is_enabled", settings->GetBool(key, false));
			} else if (type == "string") {
				props.set<std::string>("#item_name", settings->GetString(key, ""));
			} else if (type == "int") {
				props.set<std::string>("#item_name", std::to_string(settings->GetInt(key, -1)));
			}

			this->mControlCreateCallback("mod_info_factory", props);

		}
		mod.reset();
	}
};

static void ButtonHandleEvent(UiButtonHandleEvent& ev) {
	if (ev.mScreenEvent.type == ScreenEventType::ButtonEvent) {
		ButtonScreenEventData& button = ev.mScreenEvent.data.button;
		if (button.state == ButtonState::Down) {
			if (button.id == StringToNameId("button.amethyst:mods")) {
				Amethyst::GetContext().mModLoader->LoadModIcons();
				ClientInstance& ci = *Amethyst::GetClientCtx().mClientInstance;
				SceneFactory& factory = *ci.mSceneFactory;
				auto controller = std::make_shared<ModMenuScreenController>(true);
				auto scene = factory.createUIScene(*ci.mMinecraftGame, ci, "mod_menu.root_panel", controller);
				auto screen = factory._createScreen(scene);
				factory.getCurrentSceneStack()->pushScreen(screen, false);
			} else if (button.id == StringToNameId("button.menu_select")) {
				// Handle toggle buttons for mod settings
				if (button.properties->mJsonValue["$settings_namespace"].asString().empty()) return;

				bool toggle_state = button.properties->mJsonValue["#toggle_state"].asBool();
				std::string settings_namespace = button.properties->mJsonValue["$settings_namespace"].asString();
				std::string settings_id = button.properties->mJsonValue["$settings_id"].asString();

				auto modPtr = Amethyst::GetContext().mModLoader->GetModByNamespace(settings_namespace);
				auto mod = modPtr.lock();

				if (mod == nullptr) {
					Log::Info("Failed to lock mod for toggle button: {}", settings_namespace);
					return;
				}

				auto& settings = mod->mSettings;
				settings->PutBool(settings_id, toggle_state);
				mod.reset();
			}
		}
	}
}

void InitModMenuScreen() {
	auto& bus = Amethyst::GetEventBus();
	bus.AddListener<UiButtonHandleEvent>(ButtonHandleEvent);
}