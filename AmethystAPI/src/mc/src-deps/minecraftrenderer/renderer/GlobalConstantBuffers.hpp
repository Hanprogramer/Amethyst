#pragma once
#include <cstddef>
#include "ActorConstants.hpp"

namespace mce {
class GlobalConstantBuffers {
public:
	std::byte padding0[696];
	mce::ActorConstants entityConstantBuffer;
};
};