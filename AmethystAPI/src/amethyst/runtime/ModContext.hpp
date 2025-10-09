#pragma once
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/mod/Mod.hpp>

class Minecraft;
class Level;

namespace Amethyst {
	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
    void InitializeAmethystMod(AmethystContext& context, const Mod& mod);

	AmethystContext& GetContext();
	Amethyst::EventBus& GetEventBus();
	Amethyst::HookManager& GetHookManager();
	Amethyst::PatchManager& GetPatchManager();
	Amethyst::EnumAllocator& GetEnumAllocator();
	Amethyst::NetworkManager& GetNetworkManager();
	Amethyst::Platform& GetPlatform();
	
	Minecraft* GetMinecraft();
	Level* GetLevel();
	ClientInstance* GetClientInstance();

	bool IsOnAmethystThread();
	bool IsOnMainClientThread();
	bool IsOnMainServerThread();

	const Mod* GetOwnMod();
}