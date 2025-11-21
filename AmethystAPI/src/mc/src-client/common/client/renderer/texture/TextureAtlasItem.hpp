#pragma once
#include "TextureUVCoordinateSet.hpp"
#include <mc/src-deps/core/resource/ResourceHelper.hpp>
#include <mc/src-client/common/client/renderer/texture/IsotropicFaceData.hpp>

class TextureAtlasItem {
public:
    float weight;
    float _u0;
    float _v0;
    float _u1;
    float _v1;
    uint16_t _texSizeW;
	uint16_t _texSizeH;
    ResourceLocation sourceFileLocation;
    IsotropicFaceData mIsotropicFaceData;
    int16_t textureSetTranslationIndex;
    uint16_t mPBRTextureDataHandle;

	uint16_t pixelWidth() const {
		float uMax = (_u1 > _u0) ? _u1 : _u0;
		float uMin = (_u1 > _u0) ? _u0 : _u1;

		float left = roundf(uMin * _texSizeW);
		float right = roundf(uMax * _texSizeW);

		return static_cast<uint16_t>(right - left);
	}
};