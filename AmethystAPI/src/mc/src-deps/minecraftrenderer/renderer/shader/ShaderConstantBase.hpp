#pragma once
#include <cstdint>
#include <string>
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderPrimitiveTypes.hpp"

namespace mce {

class ShaderConstantBase {
public:
	std::string name;
	uint32_t numberOfElements;
	uint32_t byteOffset;
	mce::ShaderPrimitiveTypes shaderPrimitiveType;
	bool dirty;

	virtual ~ShaderConstantBase();
};

}