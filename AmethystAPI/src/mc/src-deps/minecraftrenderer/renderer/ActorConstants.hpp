#pragma once
#include "ConstantBufferConstantsBase.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantMatrix.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstantFloat.hpp"

namespace mce {

class ActorConstants : public ConstantBufferConstantsBase {
public:
	mce::ShaderConstantFloat4* OVERLAY_COLOR; // +16
	mce::ShaderConstantFloat4* TILE_LIGHT_COLOR; // +24
	mce::ShaderConstantFloat4* TILE_LIGHT_INTENSITY; // +32
	mce::ShaderConstantFloat4* CHANGE_COLOR; // +40
	mce::ShaderConstantFloat4* GLINT_COLOR; // +48
	mce::ShaderConstantFloat4* UV_ANIM; // +56
	mce::ShaderConstantFloat4* MULTIPLICATIVE_TINT_CHANGE_COLOR; // +64
	mce::ShaderConstantFloat2* UV_OFFSET; // +72
	mce::ShaderConstantFloat2* UV_ROTATION; // +80
	mce::ShaderConstantFloat2* GLINT_UV_SCALE; // +88
	// last 3 were removed from china
};

}

static_assert(sizeof(mce::ActorConstants) == 96);