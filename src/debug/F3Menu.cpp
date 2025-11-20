#include "F3Menu.hpp"


#ifdef CLIENT
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/ModContext.hpp>
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
		if (a >= 315.0f || a < 45.0f) return "south";
		if (a >= 45.0f && a < 135.0f) return "west";
		if (a >= 135.0f && a < 225.0f) return "north";
		return "east"; // guaranteed return for remaining range
	}

	void Render(AfterRenderUIEvent& event) {
		if (event.screen.visualTree->mRootControlName->mName != "hud_screen") return;
		if (!renderMenu) return;
		auto* client = Amethyst::GetClientCtx().mClientInstance;

		LocalPlayer* player = event.ctx.mClient->getLocalPlayer();
		if (!player) return;


		auto modCount = Amethyst::GetContext().mModLoader->GetModCount();
		auto ver = Amethyst::GetOwnMod()->mInfo->Version.to_string();
		std::vector<std::string> texts = { std::format("Amethyst Runtime v{} ({} mod loaded)", ver, modCount) };

		// Position info
		texts.push_back(std::format("XYZ: {} {} {}", player->getPosition()->x, player->getPosition()->y, player->getPosition()->z));
		texts.push_back(std::format("Facing: {} ({})", yawToFacing(player->getHeadRot()->y), player->getHeadRot()->y));


		// Cursor info
		ILevel* level = client->getLocalPlayer()->getLevel();
		HitResult& hr = level->getHitResult();
		if (hr.mType == HitResultType::TILE) {
			texts.push_back("");
			auto& block = client->getRegion()->getBlock(hr.mBlock);
			texts.push_back(std::format("BlockPos: {} {} {}", hr.mBlock.x, hr.mBlock.y, hr.mBlock.z));
			texts.push_back(std::format("Block: {}:{}", block.mLegacyBlock->mNameInfo.mNamespaceName, block.mLegacyBlock->mNameInfo.mRawName.getString()));
		}

		texts.push_back("");

		// Dimension info 
		const Dimension& dimension = player->getDimensionConst();
		texts.push_back("Dimension Info:");
		texts.push_back(std::format("dimension: {}", dimension.getId()));
		texts.push_back(std::format("dimension ID: {}", dimension.getDimensionId().runtimeID));

		// Invoke the event
		auto ev = F3DisplayEvent(texts, *player, hr);
		Amethyst::GetEventBus().Invoke<F3DisplayEvent>(ev);

		std::string text;
		TextMeasureData textData(1.0f, 1, false, false, false);
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
			std::regex pattern("\\§[[:alnum:]]");
			std::string result = std::regex_replace(text, pattern, "");
		}

		event.ctx.drawDebugText(rect, text, mce::Color::WHITE, 1.0f, ui::TextAlignment::Left, textData, caretData);
		event.ctx.flushText(0.0);
	}
}
#endif
