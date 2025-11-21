#pragma once
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantNull.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/ResourceBase.hpp"

namespace mce {

class ShaderConstant : public mce::ShaderConstantNull, public mce::ResourceBase<mce::ShaderConstantNull>{
public:
	virtual ~ShaderConstant();
};


}