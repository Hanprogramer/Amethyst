/// @symbolgeneration
#pragma once
#include <mc/src-deps/core/string/StringHash.hpp>
#include <mc/src/common/world/level/block/BlockShape.hpp>
#include <mc/src-client/common/client/renderer/texture/IsotropicFaceData.hpp>
#include <mc/src/common/world/level/block/BlockRenderLayer.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src-client/common/client/renderer/texture/TextureAtlasItem.hpp>
#include <mc/src/common/world/phys/AABB.hpp>
#include <amethyst/Imports.hpp>

class TextureItem {
public:
    std::string defaultName;
    std::string carriedName;
    TextureAtlasItem defaultItem;
    TextureAtlasItem carriedItem;
};

//static_assert(sizeof(TextureItem) == 192);

namespace BlockGeometry {
class Model;
};

class ResourcePackManager;
class Experiments;

class BlockGraphics {
    class ModelItem;

public:
    uintptr_t** vtable;
    IsotropicFaceData mIsotropicFaceData;
    const Block* mBlock;
    BlockRenderLayer mRenderLayer;
    BlockShape mBlockShape;
    bool mAnimatedTexture;
    float mBrightnessGamma;
    bool mFancy;
    bool mAllowSame;
    __declspec(align(4)) std::byte mSoundType[4];
    AABB mVisualShape;
    std::vector<TextureItem> mTextureItems;
    unsigned __int64 mIconTextureIndex;
    std::vector<std::vector<const BlockGeometry::Model*>> mBlockModelVariants;
    std::vector<std::vector<BlockGraphics::ModelItem>> mTessellatedModelParts;

public:
    // 1.20.71.1 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B F2 48 B8
    void setTextureItem(std::string up, std::string down, std::string north, std::string south, std::string west, std::string east);
    
    // 1.20.71.1 - 40 55 57 48 83 EC ? 48 8B 79
    void setDefaultCarriedTextures();

public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E2 48 89 95 ? ? ? ? 4C 8B F9 48 89 4D}
    MC static void initBlocks(ResourcePackManager&, const Experiments&);

    static BlockGraphics* createBlockGraphics(const HashedString& identifier, BlockShape shape);
};