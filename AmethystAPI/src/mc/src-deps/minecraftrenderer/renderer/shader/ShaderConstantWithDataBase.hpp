#pragma once
#include <glm/glm.hpp> 
#include <type_traits>
#include <cstdint>
#include "mc/src-deps/minecraftrenderer/renderer/IsA.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/shader/PrimitiveTypeFromEnumType.hpp"
#include "mc/src-deps/minecraftrenderer/renderer/shader/ShaderConstant.hpp"

namespace mce {
	
template<mce::ShaderPrimitiveTypes N>
class ShaderConstantWithDataBase : public mce::ShaderConstant, public mce::IsA<mce::ShaderPrimitiveTypes, N, uint8_t>, public mce::PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, N> { 
protected:
	using DataType = typename mce::PrimitiveTypeFromEnumType<mce::ShaderPrimitiveTypes, N>::type;
	DataType* data;	

public:
	virtual ~ShaderConstantWithDataBase() = default;

	const DataType& getData() const {
		return *data;
	}

	void setData(const DataType& newData) {
		*data = newData;
		this->dirty = true;
	}

	uint32_t getNumberOfElements() const {
		return this->numberOfElements;
	}
};

} // namespace mce
