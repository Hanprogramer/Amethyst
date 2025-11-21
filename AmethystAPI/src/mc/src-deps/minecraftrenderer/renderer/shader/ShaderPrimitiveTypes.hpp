#pragma once
#include <cstdint>

namespace mce {
enum class ShaderPrimitiveTypes : uint8_t {
	UnknownPrimitiveType = 0x0000,
	PrimitiveTypesBegin = 0x0000,
	Float1 = 0x0001,
	Float2 = 0x0002,
	Float3 = 0x0003,
	Float4 = 0x0004,
	Int1 = 0x0005,
	Int2 = 0x0006,
	Int3 = 0x0007,
	Int4 = 0x0008,
	Matrix2x2 = 0x0009,
	Matrix3x3 = 0x000a,
	Matrix3x4 = 0x000b,
	Matrix2x4 = 0x000c,
	Matrix4x4 = 0x000d,
	PrimitiveTypesEnd = 0x000d,
	Sampler1d = 0x000e,
	Sampler2d = 0x000f,
	Sampler3d = 0x0010,
	MaxShaderPrimitiveTypes = 0x0011,
};
}