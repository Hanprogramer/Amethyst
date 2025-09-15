#include "hooks/RenderingHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <minecraft/src-client/common/client/renderer/game/LevelRenderer.hpp>

SafetyHookInline _LevelRenderer_renderLevel;

class LevelRenderer;
class ScreenContext;
class FrameRenderObject;

void LevelRenderer_renderLevel(LevelRenderer* self, ScreenContext& screenContext, FrameRenderObject& frameRenderObj) {
    Amethyst::EventBus& bus = Amethyst::GetEventBus();

	BeforeRenderLevelEvent beforeEvent(*self, screenContext, frameRenderObj);
    bus.Invoke(beforeEvent);

	_LevelRenderer_renderLevel.call<void, LevelRenderer*, ScreenContext&, FrameRenderObject&>(self, screenContext, frameRenderObj);
	
	AfterRenderLevelEvent afterEvent(*self, screenContext, frameRenderObj);
    bus.Invoke(afterEvent);
}

void CreateRenderingHooks() {
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(LevelRenderer, renderLevel);
}