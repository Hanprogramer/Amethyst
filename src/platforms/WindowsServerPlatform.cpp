#include "WindowsServerPlatform.hpp"

WindowsServerPlatform::WindowsServerPlatform(HANDLE mcThreadHandle) 
	: WindowsPlatformCommon(mcThreadHandle) {}

Amethyst::PlatformType WindowsServerPlatform::GetPlatformType() const {
    return Amethyst::PlatformType::WindowsServer;
}

fs::path WindowsServerPlatform::GetComMojangPath() const {
    return fs::current_path();
}

fs::path WindowsServerPlatform::GetAmethystFolder() const {
    return fs::current_path() / "amethyst";
}
