#pragma once
#include <amethyst/Memory.hpp>

class AbstractScene {
public:
	uintptr_t** vtable;

	// virtuals
	std::string getScreenName() const {
		using function = decltype(&AbstractScene::getScreenName);
		auto func = std::bit_cast<function>(this->vtable[552 / 8]);
		Log::Info("Scene vtable {}", (uintptr_t)this->vtable);
		return (this->*func)();
	}
};