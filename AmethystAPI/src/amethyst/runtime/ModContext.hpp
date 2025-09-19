#pragma once
#include <amethyst/runtime/AmethystContext.hpp>

class Minecraft;
class Level;

namespace Amethyst {
	struct ModInfo {
	public:
		std::string name;

		ModInfo(std::string name)
			: name(std::move(name)) {}
	};

	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
	void InitializeAmethystMod(AmethystContext& context, std::unique_ptr<ModInfo> info);

	AmethystContext& GetContext();
	Amethyst::EventBus& GetEventBus();
	Amethyst::HookManager& GetHookManager();
	Amethyst::PatchManager& GetPatchManager();
	Amethyst::EnumAllocator& GetEnumAllocator();
	Amethyst::NetworkManager& GetNetworkManager();
	
	Minecraft* GetMinecraft();
	Level* GetLevel();
	ClientInstance* GetClientInstance();

	const Amethyst::ModInfo* GetOwnModInfo();
}