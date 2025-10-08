#pragma once
#include <filesystem>

namespace Amethyst {
enum class Environment {
	Client,
	Server
};

std::filesystem::path GetExecutablePath();
Environment GetEnvironment();
} // namespace Amethyst