#pragma once
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantWithDataBase.hpp"

namespace mce
{
	
template<mce::ShaderPrimitiveTypes N>
class ShaderConstantWithDataNull : public mce::ShaderConstantWithDataBase<N> {
	virtual ~ShaderConstantWithDataNull() = default;
};

} // namespace mce
