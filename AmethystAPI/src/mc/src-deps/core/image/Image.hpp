#pragma once
#include <mc/src-deps/core/container/Blob.hpp>

namespace mce {
    enum class ImageFormat : uint32_t {
        Unknown = 0x0000,
        R8Unorm = 0x0001,
        RGB8Unorm = 0x0002,
        RGBA8Unorm = 0x0003,
        COMPRESSED = 0x0004,
    };

    enum class ImageUsage : unsigned char {
        Unknown = 0x0000,
        sRGB = 0x0001,
        Data = 0x0002,
    };

    class Image {
    public:
        mce::ImageFormat imageFormat;
        unsigned int mWidth;
        unsigned int mHeight;
        unsigned int mDepth;
        ImageUsage mUsage;
        mce::Blob mImageBytes;
    };
}