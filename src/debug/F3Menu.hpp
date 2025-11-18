#pragma once


#ifdef CLIENT
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <mc/src-client/common/client/player/LocalPlayer.hpp>
#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/events/InputEvents.hpp>

namespace F3Menu {
	void Initialize();
	void Render(AfterRenderUIEvent& event);
}
#endif