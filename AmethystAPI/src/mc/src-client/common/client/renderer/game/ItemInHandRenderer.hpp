///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/renderer/MatrixStack.hpp>
#include <mc/src/common/world/item/ItemStack.hpp>
#include <mc/src-client/common/client/renderer/game/ItemContextFlags.hpp>

class BaseActorRenderContext;
class Player;
class TextureTessellator;
class ItemRenderCall;

namespace dragon { 
	struct RenderMetadata {
		int64_t mID;

		RenderMetadata(int64_t id) : mID(id) {}
		RenderMetadata(const BlockPos& pos) : mID(pos.hashCode()) {}
	};
}
namespace mce { class MaterialPtr; }
class Mob;

class ItemInHandRenderer {
public:
    std::byte padding0[216];
    ItemStack mOffhandItem;
    //int32_t mSlot;
    //IClientInstance& mClient;
    //std::unique_ptr<TextureTessellator> mTextureTessellator;
    std::byte padding368[32];
    float mHeight;
    float mOldHeight;
    float mHeightOffHand;
    float mOldHeightOffHand;

    // 1.21.0.3 - 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 44 88 4D
    void renderOffhandItem(BaseActorRenderContext& ctx, Player& player, ItemContextFlags flags);

    /// @signature {40 53 48 83 EC ? 48 8B 02 0F 57 DB"}
    MC void _transformOffhandItem(MatrixStack::MatrixStackRef& matrixStack);

    /// @signature {40 53 48 83 EC ? 48 8B 42 ? 48 8B DA 48 85 C0 74 ? 48 8B 00}
    MC bool _canTessellateAsBlockItem(const ItemStack& item) const;

	/// @sig {40 53 55 56 57 41 56 41 57 48 83 EC ? 49 8B E8}
	MC const ItemRenderCall& getRenderCallAtFrame(BaseActorRenderContext& ctx, const ItemStack& stack, int frame);

	/// @sig {41 0F B6 C0 4C 8B D2}
	MC const mce::MaterialPtr& getObjectMaterial(const ItemRenderCall& renderCall, ItemContextFlags flags) const;

	/// @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4D ? 49 8B F8}
	MC void renderObject(BaseActorRenderContext& ctx, const ItemRenderCall& renderCall, const dragon::RenderMetadata& renderMetadata, ItemContextFlags flags);

	/// @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 49 8B F9}
	MC void tessellateAtFrame(BaseActorRenderContext& ctx, Mob*, const ItemStack& stack, int frame);
};