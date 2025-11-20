#include "amethyst/runtime/AmethystContext.hpp"
#include "amethyst/runtime/mod/ModLoader.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src-deps/coregraphics/ImageDescription.hpp>
#include <mc/src-deps/coregraphics/ImageBuffer.hpp>
#include <mc/src-client/common/client/game/MinecraftGame.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Amethyst {
	ModLoader::ModLoader(AmethystContext* ctx) :
		mContext(ctx) {
	}

	ModLoader::~ModLoader() {
		UnloadAll();
		for (const auto& error : GetErrors()) {
			Log::Error("{}", error.toString());
		}
	}

	void ModLoader::LoadGraph(const ModGraph& graph) {
		UnloadAll();
		for (const auto& modInfo : graph.GetMods()) {
			auto mod = LoadSingle(modInfo);
			if (mod.expired()) {
				ModError error;
				error.Step = ModErrorStep::Loading;
				error.Type = ModErrorType::Unknown;
				error.UUID = modInfo->UUID;
				error.Message = "Failed to load mod: '{mod}'";
				error.Data["{mod}"] = modInfo->GetVersionedName();
				mErrors.push_back(error);
			} else {
				Log::Info("Loaded mod: '{}'", modInfo->GetVersionedName());
			}
		}

		for (const auto& mod : mMods) {
			auto error = mod->CallInitialize(*mContext);
			if (error.has_value()) {
				mErrors.push_back(*error);
			} else {
				Log::Info("Initialized mod: '{}'", mod->mInfo->GetVersionedName());
			}
		}
	}

	void ModLoader::LoadModIcons() {
#ifdef CLIENT
		if (Amethyst::GetClientCtx().mClientInstance == nullptr) {
			Log::Error("Can't load mod icons: No client instance found");
			return;
		}
		if (isIconLoaded) return;
		for (const auto& mod : mMods) {
			// Load the mod icon
			Log::Info("Loading mod icon for: {}", mod->mInfo->GetVersionedName());
			LoadModIcon(mod->mInfo->Directory, mod->mInfo);
		}
		isIconLoaded = true;
#endif
	}


	void ModLoader::LoadModIcon(const std::filesystem::path& path, const std::shared_ptr<const Amethyst::ModInfo>& info) {
		auto& platform = Amethyst::GetPlatform();
		fs::path iconPath = path / "icon.png";
		if (fs::exists(iconPath)) {
			Log::Info("Trying to load icon for {}", info->GetVersionedName());

			int width, height, channels;
			unsigned char* data = stbi_load(iconPath.generic_string().c_str(), &width, &height, &channels, 0);

			if (!data) {
				Log::Error("Failed to load image: {}", stbi_failure_reason());
				return;
			}

			// 2. Calculate the total size of the image data in bytes
			// Total size = width * height * number of channels per pixel
			size_t total_bytes = static_cast<size_t>(width) * height * channels;

			// 3. Create a std::vector<uint8_t> and resize it
			std::vector<uint8_t> image_data(total_bytes);

			// 4. Copy the data from the stbi_load pointer into the vector
			// Using std::copy or memcpy
			std::copy(data, data + total_bytes, image_data.begin());
			// OR: std::memcpy(image_data.data(), stbi_data, total_bytes);

			// 5. Free the memory allocated by stbi_load
			stbi_image_free(data);

			// You now have the image data in the 'image_data' vector
			std::cout << "Image data copied into vector. Total bytes: " << image_data.size() << std::endl;

			ResourceLocation loc = ResourceLocation(info->GetVersionedName());
			
			cg::ImageDescription description = cg::ImageDescription((uint32_t)width, (uint32_t)height, mce::TextureFormat::R8g8b8a8Unorm, cg::ColorSpace::sRGB, cg::ImageType::Texture2D, 1);
			cg::ImageBuffer iconImage = cg::ImageBuffer::ImageBuffer(mce::Blob(image_data.data(), image_data.size()), description);

			auto& clientCtx = Amethyst::GetClientCtx();
			clientCtx.mClientInstance->mMinecraftGame->mTextures->uploadTexture(loc, iconImage);
			Log::Info("Loaded icon for mod '{}'", info->GetVersionedName());
		}
	}

	std::weak_ptr<const Mod> ModLoader::LoadSingle(const std::shared_ptr<const ModInfo>& info) {
		auto mod = std::make_shared<Mod>(info);
		auto error = mod->Load();
		if (error.has_value()) {
			mErrors.push_back(*error);
			return {};
		}
		mMods.emplace_back(mod);
		return mod;
	}

	void ModLoader::UnloadAll() {
		mErrors.clear();
		for (auto it = mMods.rbegin(); it != mMods.rend(); ++it) {
			Unload((*it)->mInfo);
		}
	}

	void ModLoader::Unload(const std::shared_ptr<const ModInfo>& info) {
		Unload(info->UUID);
	}

	void ModLoader::Unload(const std::string& uuid) {
		auto it = std::find_if(mMods.begin(), mMods.end(), [&uuid](const std::shared_ptr<Mod>& mod) {
			return mod->mInfo->UUID == uuid;
		});
		if (it != mMods.end()) {
			auto& mod = *it;
			mod->Unload();
			mMods.erase(it);
		}
	}

	std::weak_ptr<const Mod> ModLoader::GetModByUUID(const std::string& uuid) const {
		auto it = std::find_if(mMods.begin(), mMods.end(), [&uuid](const std::shared_ptr<Mod>& mod) {
			return mod->mInfo->UUID == uuid;
		});
		if (it != mMods.end()) {
			return *it;
		}
		return {};
	}

	std::weak_ptr<const Mod> ModLoader::GetModByNamespace(const std::string& modNamespace) const {
		auto it = std::find_if(mMods.begin(), mMods.end(), [&modNamespace](const std::shared_ptr<Mod>& mod) {
			return mod->mInfo->Namespace == modNamespace;
		});
		if (it != mMods.end()) {
			return *it;
		}
		return {};
	}

	std::vector<std::weak_ptr<const Mod>> ModLoader::GetMods() const {
		std::vector<std::weak_ptr<const Mod>> mModsWeak;
		mModsWeak.reserve(mMods.size());
		std::transform(
			mMods.begin(), mMods.end(),
			std::back_inserter(mModsWeak),
			[](const std::shared_ptr<const Mod>& sp) {
			return std::weak_ptr<const Mod>(sp);
		}
		);
		return mModsWeak;
	}

	size_t ModLoader::GetModCount() const {
		return mMods.size();
	}

	const std::vector<ModError>& ModLoader::GetErrors() const {
		return mErrors;
	}

	bool ModLoader::HasErrors() const {
		return !mErrors.empty();
	}
} // namespace Amethyst