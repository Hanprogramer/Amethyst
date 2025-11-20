#pragma once
#include <variant>
#include <vector>
#include <string>

namespace Amethyst {
	using ModSettingsValue = std::variant<bool, int, std::string>;
	class ModSettings {
	public:
		std::vector<std::pair<std::string, ModSettingsValue>> values;
		ModSettings() {
		}
		~ModSettings() {
		}

		std::string GetValueType(std::string key) {
			for (const auto& pair : values) {
				if (pair.first == key) {
					Log::Info("This value of: {}:{}", key, pair.second.index());
					if (pair.second.index() == 1) {
						return "int";
					} else if (pair.second.index() == 0) {
						return "bool";
					} else if (pair.second.index() == 2) {
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
	};
}