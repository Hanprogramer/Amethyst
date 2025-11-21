#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include "amethyst/game/capabilities/BaseCapability.hpp"
#include "amethyst/game/capabilities/CapabilityRegistry.hpp"
#include <mc/src/common/world/level/block/Block.hpp>

class Level;
class BlockPos;
class Block;
class BlockActor;
class BlockLegacy;

template <typename T, typename C>
class BlockCapability : public BaseCapability {
public:
	using ProviderFn = std::function<T*(Level&, const BlockPos&, const Block&, BlockActor*, const C&)>;
private:
	bool proxyable;
	std::unordered_map<const BlockLegacy*, std::vector<ProviderFn>> providers;

public:
	CapabilityRegistry<BlockCapability<T, C>> registry;

	BlockCapability<T, C>& create(const HashedString& name) {
		return registry.create(name);
	}

	BlockCapability<T, C>& createVoid(const HashedString& name) {
		return registry.create(name);
	}

	BlockCapability<T, C>& createSided(const HashedString& name) {
		return registry.create(name);
	}

	std::vector<BlockCapability<T, C>> getAll() {
		return registry.getAll();
	}

	BlockCapability(const HashedString& name) 
		: BaseCapability(name), proxyable(false),
		registry([](const HashedString& name) {
			return std::make_unique<BlockCapability<T, C>>(name);
		}) {}

	void setProxyable(bool value) {
		proxyable = value;
	}

	bool isProxyable() const {
		return proxyable;
	}

	void addProvider(const BlockLegacy* block, ProviderFn provider) {
		providers[block].push_back(provider);
	}

	T* getCapability(Level& level, const BlockPos& pos, const Block& state, BlockActor* blockEntity, const C& side) {
		auto it = providers.find(static_cast<const BlockLegacy*>(state.mLegacyBlock.get()));
		if (it == providers.end()) {
			return nullptr;
		}

		for (const auto& provider : it->second) {
			T* capability = provider(level, pos, state, blockEntity, side);
			if (capability != nullptr) {
				return capability;
			}
		}

		return nullptr;
	}
};