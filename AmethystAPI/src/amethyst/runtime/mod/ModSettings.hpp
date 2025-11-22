#pragma once
#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include <mc/src-client/common/client/gui/controls/UIPropertyBag.hpp>
#include <amethyst/runtime/mod/Mod.hpp>

namespace Amethyst {
	using ModSettingsValue = std::variant<bool, int, float, std::string>;
	class ModSettings; // Forward declaration

	class ModSettingsHint {
	public:
		// Base class for settings hints
		virtual ~ModSettingsHint() = default;
		virtual std::string GetControlId() const = 0;
		virtual void PopulateProps(const std::shared_ptr<ModSettings>& settings, std::string key, UIPropertyBag& props) const = 0;
	};

	class SliderSettingsHint : public ModSettingsHint {
	public:
		float minValue;
		float maxValue;
		float step;

		SliderSettingsHint(float min, float max, float step);
		std::string GetControlId() const override;
		void PopulateProps(const std::shared_ptr<ModSettings>& settings, std::string key, UIPropertyBag& props) const override;
	};

	class EnumOptionsSettingsHint : public ModSettingsHint {
	public:
		std::vector<std::string> possibleValues;

		EnumOptionsSettingsHint(std::vector<std::string> possibleValues);
		std::string GetControlId() const override;
		void PopulateProps(const std::shared_ptr<ModSettings>& settings, std::string key, UIPropertyBag& props) const override;
	};

	class ModSettings {
	public:
		std::vector<std::pair<std::string, ModSettingsValue>> values;
		std::map<std::string, std::shared_ptr<ModSettingsHint>> hints;

		ModSettings();
		~ModSettings();

		void SetHintFor(const std::string& key, const std::shared_ptr<ModSettingsHint>& hint);
		std::shared_ptr<ModSettingsHint> GetHintFor(const std::string& key);
		bool HasHint(const std::string& key) const;
		std::string GetValueType(std::string key);
		std::vector<std::string> GetSettingsKeys();

		bool HasKey(std::string key);

		int GetInt(std::string key, int defaultVal);
		bool GetBool(std::string key, bool defaultVal);
		std::string GetString(std::string key, std::string defaultVal);
		float GetFloat(std::string key, float defaultVal);

		void PutInt(std::string key, int value);
		void PutBool(std::string key, bool value);
		void PutString(std::string key, std::string value);
		void PutFloat(std::string key, float value);
	};
}