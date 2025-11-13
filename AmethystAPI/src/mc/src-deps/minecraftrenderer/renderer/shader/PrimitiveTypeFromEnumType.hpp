#pragma once
#include <glm/glm.hpp>
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderPrimitiveTypes.hpp"

namespace mce { 
template<typename EnumType, EnumType Value>
struct PrimitiveTypeFromEnumType;

template<>
struct PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, mce::ShaderPrimitiveTypes::Float1> {
    using type = float;
};

template<>
struct PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, mce::ShaderPrimitiveTypes::Float2> {
    using type = glm::vec2;
};

template<>
struct PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, mce::ShaderPrimitiveTypes::Float3> {
    using type = glm::vec3;
};

template<>
struct PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, mce::ShaderPrimitiveTypes::Float4> {
    using type = glm::vec4;
};
}