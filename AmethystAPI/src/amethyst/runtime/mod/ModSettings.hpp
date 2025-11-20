#pragma once
#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include <mc/src-client/common/client/gui/controls/UIPropertyBag.hpp>

namespace Amethyst {
	using ModSettingsValue = std::variant<bool, int, float, std::string>;

	class ModSettingsHint {
	public:
		// Base class for settings hints
		virtual std::string GetControlId() const = 0;
		virtual void PopulateProps(UIPropertyBag& props) const = 0;
	};

	class SliderSettingsHint : public ModSettingsHint {
	public:
		float minValue;
		float maxValue;
		float step;

		SliderSettingsHint(float min, float max, float step)
			: minValue(min), maxValue(max), step(step) {
		}

		std::string GetControlId() const override {
			return "mod_settings_item_slider";
		}

		void PopulateProps(UIPropertyBag& props) const override {
			props.set<float>("$min_value", minValue);
			props.set<float>("$max_value", maxValue);
			props.set<float>("$step", step);
		}
	};

	class EnumOptionsSettingsHint : public ModSettingsHint {
	public:
		std::vector<std::string> possibleValues;

		EnumOptionsSettingsHint(std::vector<std::string> possibleValues) :
			possibleValues(possibleValues) {
		}

		std::string GetControlId() const override {
			return "mod_settings_item_options";
		}

		void PopulateProps(UIPropertyBag& props) const override {

		}
	};

	class ModSettings {
	public:
		std::vector<std::pair<std::string, ModSettingsValue>> values;
		std::map<std::string, std::shared_ptr<ModSettingsHint>> hints;

		ModSettings() {
		}
		~ModSettings() {
		}

		void SetHintFor(const std::string& key, const std::shared_ptr<ModSettingsHint>& hint) {
			hints[key] = hint;
		}

		std::shared_ptr<ModSettingsHint>& GetHintFor(std::string key) {
			return hints[key];
		}

		bool HasHint(std::string key) const {
			return hints.contains(key);
		}

		std::string GetValueType(std::string key) {
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



		std::vector<std::string> GetSettingsKeys() {
			std::vector<std::string> keys;
			for (auto& pair : values) {
				keys.push_back(pair.first);
			}
			return keys;
		}

		bool HasKey(std::string key) {
			for (auto& pair : values) {
				if (pair.first == key) {
					return true;
				}
			}
			return false;
		}

		int GetInt(std::string key, int defaultVal) {
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
		bool GetBool(std::string key, bool defaultVal) {
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

		std::string GetString(std::string key, std::string defaultVal) {
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
		float GetFloat(std::string key, float defaultVal) {
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

		void PutInt(std::string key, int value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = ModSettingsValue{ value };
					return;
				}
			}
			values.push_back({ key, ModSettingsValue{value} });
		}
		void PutBool(std::string key, bool value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = ModSettingsValue{ value };
					return;
				}
			}
			values.push_back({ key, ModSettingsValue{value} });
		}
		void PutString(std::string key, std::string value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = ModSettingsValue{ value };
					return;
				}
			}
			values.push_back({ key, ModSettingsValue{value} });
		}
		void PutFloat(std::string key, float value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = ModSettingsValue{ value };
					return;
				}
			}
			values.push_back({ key, ModSettingsValue{value} });
		}
	};
}