#include "F3Menu.hpp"


#ifdef CLIENT
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/mod/ModSettings.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/events/InputEvents.hpp>
#include <mc/src-client/common/client/player/LocalPlayer.hpp>
#include <mc/src-client/common/client/gui/ScreenView.hpp>
#include <mc/src-client/common/client/gui/gui/UIControl.hpp>
#include <mc/src-client/common/client/gui/gui/VisualTree.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <mc/src/common/world/level/BlockSource.hpp>
#include <mc/src/common/locale/I18n.hpp>
#include <amethyst/runtime/events/UiEvents.hpp>
#include <regex>

namespace F3Menu {
	static bool renderMenu = false;

	void Initialize() {
		Amethyst::GetEventBus().AddListener<AfterRenderUIEvent>(Render);
		Amethyst::GetEventBus().AddListener<RegisterInputsEvent>([&](RegisterInputsEvent ev) {
			Amethyst::InputManager& input = ev.inputManager;
			auto& action = input.RegisterNewInput("amethyst.toggle_debug_ui", { 114 }, true, Amethyst::KeybindContext::Gameplay);

			action.addButtonUpHandler([](FocusImpact, ClientInstance&) {
				renderMenu = !renderMenu;
				return Amethyst::InputPassthrough::Passthrough;
			});
		});
	}

	static std::string yawToFacing(float yawDegrees) {
		// normalize to [0, 360)
		float a = std::fmod(yawDegrees, 360.0f);
		if (a < 0) a += 360.0f;

		// each sector is 90 degrees, centered on 0=south, 90=west, 180=north, 270=east
		if (a >= 315.0f || a < 45.0f) return "South (Towards positive Z)";
		if (a >= 45.0f && a < 135.0f) return "West (Towards negative X)";
		if (a >= 135.0f && a < 225.0f) return "North (Towards negative Z)";
		return "East (Towards positive X)"; // guaranteed return for remaining range
	}

	static std::unordered_map<std::string, int> getAllBlockStates(const Block& block) {
		std::unordered_map<std::string, int> result;

		BlockState::StateListNode* node = BlockState::StateListNode::mHead;
		while (node) {
			const BlockState* state = node->mState;
			const std::string name = state->mName.getString();

			if (block.hasState(*state)) {
				int value = block.getState<int>(*state);
				result[name] = value;
			}
			
			node = node->mNext;
		}

		return result;
	}

	void Render(AfterRenderUIEvent& event) {
		if (event.screen.visualTree->mRootControlName->mName != "hud_screen") return;
		if (!renderMenu) return;
		auto* client = Amethyst::GetClientCtx().mClientInstance;

		LocalPlayer* player = event.ctx.mClient->getLocalPlayer();
		if (!player) return;


		auto modCount = Amethyst::GetContext().mModLoader->GetModCount();
		auto ver = Amethyst::GetOwnMod()->mInfo->Version.to_string();
		std::vector<std::string> texts = { };
		texts.push_back(std::format("Minecraft 1.21.0.3 (Amethyst v{}, {} mods)", ver, modCount));

		// Position info
		texts.push_back(std::format("§cX§aY§bZ: §c{:.3f} §a{:.3f} §b{:.3f}§r", player->getPosition()->x, player->getPosition()->y, player->getPosition()->z));

		// Cursor info
		ILevel* level = client->getLocalPlayer()->getLevel();
		HitResult& hr = level->getHitResult();

		// Dimension info 
		const Dimension& dimension = player->getDimensionConst();
		texts.push_back(std::format("§2Dimension: §b{} ({})§r", dimension.getId(), dimension.getDimensionId().runtimeID));
		const Vec2& headRot = *player->getHeadRot();
		texts.push_back(std::format("§2Facing: §b{}", yawToFacing(headRot.y)));
		texts.push_back(std::format("§2Rotation: §bYaw {:.1f} Pitch {:.1f}", headRot.x, headRot.y));

		// Looked at block
		if (hr.mType == HitResultType::TILE) {
		 	// texts.push_back("");
		 	auto& block = client->getRegion()->getBlock(hr.mBlock);
		 	texts.push_back(std::format("§uTargeted Block: §e{} {} {}", hr.mBlock.x, hr.mBlock.y, hr.mBlock.z));
		 	texts.push_back(std::format("§uBlock ID: §e{}", block.mLegacyBlock->mNameInfo.mFullName.getString()));

			auto states = getAllBlockStates(block);
			for (const auto& [name, value] : states) {
				texts.push_back(std::format("§u{}: §e{}", name, value));
			}
		}

		// Invoke the event
		auto ev = F3DisplayEvent(texts, *player, hr);
		Amethyst::GetEventBus().Invoke<F3DisplayEvent>(ev);

		std::string text;
		TextMeasureData textData(1.0f, 1, false, false, false);
		textData.renderShadow = true;
		CaretMeasureData caretData(0, false);
		auto font = Bedrock::NonOwnerPointer<const FontHandle>(&event.ctx.mDebugTextFontHandle);

		// Draw the background
		float ypos = 1.0f;
		for (int i = 0; i < texts.size(); i++) {
			text += texts.at(i) + "\n";
			auto mr = event.ctx.mMeasureStrategy.measureText(font, texts.at(i), 300, 300, textData, caretData);
			if(!(texts.at(i).empty()))
				event.ctx.fillRectangle(RectangleArea{ 0.0f, mr.mSize.x + 3.0f, ypos, ypos + mr.mSize.y}, mce::Color::FONT_DARK_GRAY, 0.5f);
			ypos += mr.mSize.y;
		}

		// Draw the text
		RectangleArea rect{ 2.0f, 100.0f, 2.0f, 700.0f };

		if (Amethyst::GetOwnMod()->mSettings->GetBool("disable_f3_colors", false)) {
			// Use std::regex_replace to find all matches and replace them with an empty string ("")
			std::regex pattern("\\�[[:alnum:]]");
			std::string result = std::regex_replace(text, pattern, "");
		}

		event.ctx.drawDebugText(rect, text, mce::Color::WHITE, 1.0f, ui::TextAlignment::Left, textData, caretData);
		event.ctx.flushText(1.0);
	}
}
#endif
