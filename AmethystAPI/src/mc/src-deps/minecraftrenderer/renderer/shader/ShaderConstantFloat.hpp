#pragma once
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantWithDataBase.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderPrimitiveTypes.hpp"

namespace mce {

class ShaderConstantFloat4 : public mce::ShaderConstantWithDataBase<mce::ShaderPrimitiveTypes::Float4> {

};

class ShaderConstantFloat2 : public mce::ShaderConstantWithDataBase<mce::ShaderPrimitiveTypes::Float2> {
};
}