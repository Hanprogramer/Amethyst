#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

/**
 * Fired to register capability providers at an appropriate time.
 */
class RegisterCapabilitiesEvent : public BaseEvent {
public:
	Amethyst::Capabilities& capabilities;

    RegisterCapabilitiesEvent(Amethyst::Capabilities& capabilities) 
		: capabilities(capabilities) {}


	// BLOCKS
	template<typename T, typename C> 
	void registerBlockEntity(BlockCapability<T, C>& capability, const BlockLegacy* block, typename BlockCapability<T, C>::ProviderFn provider) {
		// TODO add a wrapper like the original does..

		capability.addProvider(block, provider);
	}
};