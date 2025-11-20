#pragma once
#include <variant>
#include <vector>
#include <string>

namespace Amethyst {
	using ModSettingsValue = std::variant<int, bool, std::string>;
	class ModSettings {
	private:
		std::vector<std::pair<std::string, ModSettingsValue>> values;
	public:
		ModSettings() {
		}
		~ModSettings() {
		}

		std::vector<std::string> GetKeys() {
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
					pair.second = value;
					return;
				}
			}
			values.push_back({ key, value });
		}
		void PutBool(std::string key, bool value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = value;
					return;
				}
			}
			values.push_back({ key, value });
		}
		void PutString(std::string key, std::string value) {
			for (auto& pair : values) {
				if (pair.first == key) {
					pair.second = value;
					return;
				}
			}
			values.push_back({ key, value });
		}
	};
}