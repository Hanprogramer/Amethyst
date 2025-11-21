#include "ModSettings.hpp"

namespace Amethyst {
	SliderSettingsHint::SliderSettingsHint(float min, float max, float step)
		: minValue(min), maxValue(max), step(step) {
	}

	std::string SliderSettingsHint::GetControlId() const {
		return "mod_settings_item_slider";
	}

	void SliderSettingsHint::PopulateProps(const std::shared_ptr<ModSettings>& settings, std::string key, UIPropertyBag& props) const {
		props.set<float>("$min_value", minValue);
		props.set<float>("$max_value", maxValue);
		props.set<float>("$step", step);
	}

	EnumOptionsSettingsHint::EnumOptionsSettingsHint(std::vector<std::string> possibleValues) :
		possibleValues(possibleValues) {
	}

	std::string EnumOptionsSettingsHint::GetControlId() const {
		return "mod_settings_item_options";
	}

	void EnumOptionsSettingsHint::PopulateProps(const std::shared_ptr<ModSettings>& settings, std::string key, UIPropertyBag& props) const {
	}


	ModSettings::ModSettings() {
	}

	ModSettings::~ModSettings() {
	}

	void ModSettings::SetHintFor(const std::string& key, const std::shared_ptr<ModSettingsHint>& hint) {
		hints[key] = hint;
	}

	std::shared_ptr<ModSettingsHint> ModSettings::GetHintFor(const std::string& key) {
		auto it = hints.find(key);
		if (it != hints.end()) {
			return it->second; // may still be nullptr, so caller must check
		}
		return nullptr;
	}


	bool ModSettings::HasHint(std::string key) const {
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