#include "ModSettings.hpp"

namespace Amethyst {
	SliderSettingsHint::SliderSettingsHint(float min, float max, float step)
		: minValue(min), maxValue(max), step(step) {
	}

	std::string SliderSettingsHint::GetControlId(std::string modNamespace, std::string key) const {
		return "mod_settings_item_slider";
	}

	void SliderSettingsHint::PopulateProps(ScreenController* controller, std::string controlId, std::string controlName, const std::shared_ptr<ModSettings>& settings, std::string modNamespace, std::string key, UIPropertyBag& props) const {
		props.set<float>("$min_value", minValue);
		props.set<float>("$max_value", maxValue);
		props.set<float>("$step", step);
	}

	EnumOptionsSettingsHint::EnumOptionsSettingsHint(std::vector<std::string> possibleValues) :
		possibleValues(possibleValues) {
	}

	std::string EnumOptionsSettingsHint::GetControlId(std::string modNamespace, std::string key) const {
		return "mod_settings_item_options";
	}

	void EnumOptionsSettingsHint::PopulateProps(ScreenController* controller, std::string controlId, std::string controlName, const std::shared_ptr<ModSettings>& settings, std::string modNamespace, std::string key, UIPropertyBag& props) const {
		// Bind for the visibility of the content popup
		controller->bindBool(std::format("#{}", controlName),
			[this]() { return this->opened; },
			[&]() { return true; });
		controller->bindStringForAnyCollection("mycollection", 
			[](std::string coll, int ind) { return "HELLOWW!";  }, 
			[](std::string coll, int ind) { return true; });

		auto typeName = [](Json::ValueType t) {
			switch (t) {
			case Json::nullValue: return "null";
			case Json::intValue: return "int";
			case Json::uintValue: return "uint";
			case Json::realValue: return "real";
			case Json::stringValue: return "string";
			case Json::booleanValue: return "bool";
			case Json::arrayValue: return "array";
			case Json::objectValue: return "object";
			default: return "unknown";
			}
		};



		//Json::Reader reader;

		//reader.parse(R"([
		//	  {
		//		"storage_location_option_external@settings_common.radio_with_label": {
		//		  "$toggle_state_binding_name": "#storage_location_radio_external",
		//		  "$radio_label_text": "HELLOOO"
		//		}
		//	  },
		//	  {
		//		"storage_location_option_appdata@settings_common.radio_with_label": {
		//		  "$toggle_state_binding_name": "#storage_location_radio_package",
		//		  "$radio_label_text": "ME OPTION 2"
		//		}
		//	  }
		//	])", root, false);

		//Log::Info("JSON root: {}", root.toStyledString());

		Json::Value root = Json::Value(Json::objectValue);
		root["A"] = Json::Value("A string");
		root["B"] = Json::Value("me a string");
		root["C"] = Json::Value(3.14);
		Log::Info("Value of root: {}", root.toStyledString());
		Log::Info("Value of root[\"B\"]: {}", root["B"].asString());

		Log::Info("option_radio_buttons before assignment: {}", typeName(props.mJsonValue["$option_radio_buttons"].type()));
		props.mJsonValue["$option_radio_buttons"] = root;
		Log::Info("option_radio_buttons after assignment: {}", typeName(props.mJsonValue["$option_radio_buttons"].type()));

		Log::Info("Value of root after assign: {}", root.toStyledString());

		Log::Info("props.mJsonValue: {}, is of value: {}", props.mJsonValue.toStyledString(), typeName(props.mJsonValue["$option_radio_buttons"].type()));
	}


	ModSettings::ModSettings() {
	}

	ModSettings::~ModSettings() {
	}

	void ModSettings::SetHintFor(const std::string& key, const std::shared_ptr<ModSettingsHint>& hint) {
		if (!hint) {
			Log::Error("Attempted to set null hint for key '{}'", key);
			return;
		}
		hints[key] = hint;
	}

	std::shared_ptr<ModSettingsHint> ModSettings::GetHintFor(const std::string& key) {
		auto it = hints.find(key);
		return it != hints.end() ? it->second : nullptr;
		return nullptr;
	}


	bool ModSettings::HasHint(const std::string& key) const {
		return hints.contains(key);
	}

	std::string ModSettings::GetValueType(std::string key) {
		for (const auto& pair : values) {
			if (pair.first == key) {
				if (pair.second.index() == 0) {
					return "bool";
				} else if (pair.second.index() == 1) {
					return "int";
				} else if (pair.second.index() == 2) {
					return "float";
				} else if (pair.second.index() == 3) {
					return "string";
				}
			}
		}
		return "none";
	}



	std::vector<std::string> ModSettings::GetSettingsKeys() {
		std::vector<std::string> keys;
		for (auto& pair : values) {
			keys.push_back(pair.first);
		}
		return keys;
	}

	bool ModSettings::HasKey(std::string key) {
		for (auto& pair : values) {
			if (pair.first == key) {
				return true;
			}
		}
		return false;
	}

	int ModSettings::GetInt(std::string key, int defaultVal) {
		for (auto& pair : values) {
			if (pair.first == key) {
				if (std::holds_alternative<int>(pair.second)) {
					return std::get<int>(pair.second);
				}
				break;
			}
		}
		return defaultVal;
	}
	bool ModSettings::GetBool(std::string key, bool defaultVal) {
		for (auto& pair : values) {
			if (pair.first == key) {
				if (std::holds_alternative<bool>(pair.second)) {
					return std::get<bool>(pair.second);
				}
				break;
			}
		}
		return defaultVal;
	}

	std::string ModSettings::GetString(std::string key, std::string defaultVal) {
		for (auto& pair : values) {
			if (pair.first == key) {
				if (std::holds_alternative<std::string>(pair.second)) {
					return std::get<std::string>(pair.second);
				}
				break;
			}
		}
		return defaultVal;
	}
	float ModSettings::GetFloat(std::string key, float defaultVal) {
		for (auto& pair : values) {
			if (pair.first == key) {
				if (std::holds_alternative<float>(pair.second)) {
					return std::get<float>(pair.second);
				}
				break;
			}
		}
		return defaultVal;
	}

	void ModSettings::PutInt(std::string key, int value) {
		for (auto& pair : values) {
			if (pair.first == key) {
				pair.second = ModSettingsValue{ value };
				return;
			}
		}
		values.push_back({ key, ModSettingsValue{value} });
	}
	void ModSettings::PutBool(std::string key, bool value) {
		for (auto& pair : values) {
			if (pair.first == key) {
				pair.second = ModSettingsValue{ value };
				return;
			}
		}
		values.push_back({ key, ModSettingsValue{value} });
	}
	void ModSettings::PutString(std::string key, std::string value) {
		for (auto& pair : values) {
			if (pair.first == key) {
				pair.second = ModSettingsValue{ value };
				return;
			}
		}
		values.push_back({ key, ModSettingsValue{value} });
	}
	void ModSettings::PutFloat(std::string key, float value) {
		for (auto& pair : values) {
			if (pair.first == key) {
				pair.second = ModSettingsValue{ value };
				return;
			}
		}
		values.push_back({ key, ModSettingsValue{value} });
	}
}