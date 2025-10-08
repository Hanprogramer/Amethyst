#pragma once
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;

namespace Amethyst {
enum class PlatformType : uint8_t {
	WindowsClient, 
	WindowsServer
};

class Platform {
public:
	virtual ~Platform() = default;
	virtual PlatformType GetPlatformType() const = 0;
	virtual fs::path GetComMojangPath() const = 0;
	virtual fs::path GetAmethystFolder() const = 0;
	virtual void AttachDebugger() = 0;
    virtual void InitializeConsole() = 0;
	virtual void PauseGameThread() = 0;
	virtual void ResumeGameThread() = 0;

	// todo put in funcs that abstract loading mod dlls (since android will be different if we target that)
	// things like getting mod funcs from the loaded things
	// unloading mods
	// etc
};

} // namespace Amethyst