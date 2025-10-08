#pragma once
#include <filesystem>

namespace Amethyst {
enum class Environment : unsigned char {
	Client,
	Server
};

const std::filesystem::path& GetExecutablePath();
Environment GetEnvironment();
} // namespace Amethyst