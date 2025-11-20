#include "loader/AmethystRuntime.hpp"

#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "amethyst/runtime/events/InputEvents.hpp"
#include "debug/AmethystDebugging.hpp"
#include "loader/RuntimeContext.hpp"

#include "mc/src-deps/coregraphics/ImageBuffer.hpp"
#include "mc/src-deps/core/image/Image.hpp"
#include "mc/src-client/common/client/game/MinecraftGame.hpp"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

AmethystRuntime::AmethystRuntime(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread)
	: mAmethystContext(std::move(platform), amethystThread) {
	AmethystRuntime::instance = this;
}

void AmethystRuntime::Start() {
	Assert(!mRunning, "AmethystRuntime::Start called whilst running!");
	auto& platform = Amethyst::GetPlatform();

	// read the config file and load in any mods
	ReadLauncherConfig();

	// Prompt a debugger if they are in developer mode
	if (mLauncherConfig.promptDebugger)
		platform.AttachDebugger();

	Amethyst::GetContext().Start();

	// Load all mod DLLs and call their initialize functions
	LoadModDlls();
	mRunning = true;
	RunMods();
}

void AmethystRuntime::ReadLauncherConfig() {
	// Ensure it exists
	auto& platform = Amethyst::GetPlatform();
	fs::path launcherConfigPath = platform.GetAmethystFolder() / "launcher_config.json";

	if (!fs::exists(launcherConfigPath)) {
		throw std::exception("launcher_config.json could not be found!");
	}

	// Try to read it to a std::string
	std::ifstream configFile(launcherConfigPath);
	if (!configFile.is_open()) {
		throw std::exception("Failed to open launcher_config.json");
	}

	// Read into a std::string
	std::stringstream buffer;
	buffer << configFile.rdbuf();
	configFile.close();
	std::string fileContents = buffer.str();

	mLauncherConfig = Config(fileContents);
	mLauncherConfig.mods.insert(mLauncherConfig.mods.begin(), mLauncherConfig.injectedMod);
}

void AmethystRuntime::LoadModDlls() {
	Amethyst::ModRepository& repository = *mAmethystContext.mModRepository;
	Amethyst::ModGraph& modGraph = *mAmethystContext.mModGraph;
	Amethyst::ModLoader& modLoader = *mAmethystContext.mModLoader;

	// Register mod inputs
	// On game start mOptions will be nullptr, but the register inputs event gets called when options is created.
	// When hot-reloading we will have options already so we can register inputs here.
#ifdef CLIENT
	if (Amethyst::GetClientCtx().mOptions != nullptr) {
		RegisterInputsEvent event(*Amethyst::GetContext().mInputManager.get());
		Amethyst::GetEventBus().Invoke(event);
	}
#endif

	// Scan the mods directory for mod.json files and load them into the repository
	auto& platform = Amethyst::GetPlatform();
	repository.ScanDirectory(platform.GetAmethystFolder() / "mods", true);

	// Add itself as a mod to the repository to resolve dependencies against
	auto info = Amethyst::Mod::GetInfo(mLauncherConfig.injectedMod);

	repository.AddMod(repository.GetMods().cbegin(), info);
	modGraph.SortAndValidate(repository, mLauncherConfig.mods);

	for (const auto& modInfo : modGraph.GetMods()) {
		if (modInfo->UUID == "00000000-0000-0000-0000-000000000000") {
			Log::Warning("Mod '{}' has the default UUID of '00000000-0000-0000-0000-000000000000' in its mod.json! It is recommended to generate a new one", modInfo->GetVersionedName());
		}

		// Load the mod icon
//#ifdef CLIENT
		if (Amethyst::GetClientCtx().mClientInstance != nullptr) {
			Log::Info("Is client side");
			LoadModIcon(modInfo->Directory, modInfo);
		} else {

			Log::Info("Is not client side");
		}
//#endif
	}

	for (const auto& error : modGraph.GetErrors()) {
		Log::Error("{}", error.toString());
	}

	modLoader.LoadGraph(modGraph);
	for (const auto& error : modLoader.GetErrors()) {
		Log::Error("{}", error.toString());
	}


	// Allow mods to add listeners to eachothers events
	AddModEventListenersEvent event;
	Amethyst::GetEventBus().Invoke<AddModEventListenersEvent>(event);
}

void AmethystRuntime::LoadModIcon(const std::filesystem::path& path, const std::shared_ptr<const Amethyst::ModInfo>& info) {
	auto& platform = Amethyst::GetPlatform();
	fs::path iconPath = path / "icon.png";
	if (fs::exists(iconPath)) {
		Log::Info("Trying to load icon for {}", info->GetVersionedName());
		std::ifstream iconFile(iconPath, std::ios::binary);
		if (iconFile.is_open()) {
			std::vector<uint8_t> iconData((std::istreambuf_iterator<char>(iconFile)), std::istreambuf_iterator<char>());
			ResourceLocation loc = ResourceLocation(info->GetVersionedName());

			cg::ImageDescription description = cg::ImageDescription((uint32_t)32, (uint32_t)32, mce::TextureFormat::R8g8b8a8Unorm, cg::ColorSpace::sRGB, cg::ImageType::Texture2D, (uint32_t)iconData.size());
			cg::ImageBuffer iconImage = cg::ImageBuffer::ImageBuffer(mce::Blob(iconData.data(), iconData.size()), description);

			auto& clientCtx = Amethyst::GetClientCtx();
			clientCtx.mClientInstance->mMinecraftGame->mTextures->uploadTexture(loc, iconImage);
			iconFile.close();
			Log::Info("Loaded icon for mod '{}'", info->GetVersionedName());
		}
	}
}
void AmethystRuntime::RunMods() {
	auto& platform = Amethyst::GetPlatform();
	platform.ResumeGameThread();

	// Listen for hot-reload and keep Amethyst running until the end
	while (true) {
		Sleep(1000 / 20);

		if (platform.HasRequestedStop()) break;

		if (platform.HasRequestedHotReload() && mRunning == true) {
			Log::Info("\n========================= Starting hot-reload! =========================");

			platform.PauseGameThread();
			Shutdown();

			return Start();
		}
	}
}

void AmethystRuntime::Shutdown() {
	if (!mRunning)
		return;

	BeforeModShutdownEvent shutdownEvent;
	Amethyst::GetEventBus().ReverseInvoke(shutdownEvent);

	// Clear lists of mods & functions.
	Amethyst::GetContext().Shutdown();
	mRunning = false;
}

extern "C" __declspec(dllexport)
AmethystContext* GetContextInstance() {
	return &Amethyst::GetContext();
}
