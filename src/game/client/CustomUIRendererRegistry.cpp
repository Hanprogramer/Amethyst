#ifdef CLIENT
#include "CustomUIRendererRegistry.hpp"
#include <mc/src-client/common/client/gui/controls/UIControlFactory.hpp>
#include <mc/src-client/common/client/gui/controls/CustomRenderComponent.hpp>
#include <mc/src-client/common/client/gui/UIResolvedDef.hpp>
#include <mc/src-client/common/client/gui/gui/UIControl.hpp>
#include "game/client/CustomUIRendererRegistry.hpp"
#include <mc/src-client/common/client/gui/controls/renderers/MinecraftUICustomRenderer.hpp>

Amethyst::InlineHook<decltype(&UIControlFactory::_populateCustomRenderComponent)> _UIControlFactory__populateCustomRenderComponent;

void UIControlFactory__populateCustomRenderComponent(UIControlFactory* factory, const UIResolvedDef& resolved, UIControl& control) {
	auto* modComponentsFactory = (CustomUIRendererRegistry*)Amethyst::GetClientCtx().mCustomUIRendererRegistry.get();

	if (!modComponentsFactory) {
		_UIControlFactory__populateCustomRenderComponent(factory, resolved, control);
		return;
	}

	std::string rendererType = resolved.getAsString("renderer");

	auto customComponent = modComponentsFactory->tryCreateRenderer(rendererType);
	Log::Info("Trying to create custom renderer with id '{}': {}", rendererType, customComponent ? "Found" : "Not Found");
	if (customComponent) {
		control.setComponent<CustomRenderComponent>(
			std::make_unique<CustomRenderComponent>(control)
		);

		CustomRenderComponent* component = control.getComponent<CustomRenderComponent>();
		component->setRenderer(customComponent);
		return;
	}

	_UIControlFactory__populateCustomRenderComponent(factory, resolved, control);
}

void CustomUIRendererRegistry::AddEventListeners() {
	auto& hooks = Amethyst::GetHookManager();
	HOOK(UIControlFactory, _populateCustomRenderComponent);
}
#endif