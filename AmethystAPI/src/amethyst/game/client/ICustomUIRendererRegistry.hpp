#pragma once
#include <functional>
#include <string>
#include <memory>

class MinecraftUICustomRenderer;

namespace Amethyst {

class ICustomUIRendererRegistry {
public:
	virtual void registerRenderer(const std::string& id, std::function<std::shared_ptr<MinecraftUICustomRenderer>(void)> factory) = 0;

	ICustomUIRendererRegistry() = default;

    ICustomUIRendererRegistry(const ICustomUIRendererRegistry&) = delete;
    ICustomUIRendererRegistry& operator=(const ICustomUIRendererRegistry&) = delete;

    ICustomUIRendererRegistry(ICustomUIRendererRegistry&&) = delete;
    ICustomUIRendererRegistry& operator=(ICustomUIRendererRegistry&&) = delete;
};

}