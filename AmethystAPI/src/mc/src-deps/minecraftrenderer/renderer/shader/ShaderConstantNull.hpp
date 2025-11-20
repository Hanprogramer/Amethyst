#pragma once
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantBase.hpp"

namespace mce {

class ShaderConstantNull : public mce::ShaderConstantBase {
public:
	virtual ~ShaderConstantNull();
};

}