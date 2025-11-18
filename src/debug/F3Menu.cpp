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

	std::string yawToFacing(float yawDegrees) {
		// normalize to [0, 360)
		float a = std::fmod(yawDegrees, 360.0f);
		if (a < 0) a += 360.0f;

		// each sector is 90 degrees, centered on 0=north, 90=east, 180=south, 270=west
		if (a >= 315.0f || a < 45.0f) return "north";
		if (a >= 45.0f && a < 135.0f) return "east";
		if (a >= 135.0f && a < 225.0f) return "south";
		return "west"; // guaranteed return for remaining range
	}

	void Render(AfterRenderUIEvent& event) {
		if (event.screen.visualTree->mRootControlName->mName != "hud_screen") return;
		if (!renderMenu) return;
		auto* client = Amethyst::GetClientCtx().mClientInstance;

		LocalPlayer* player = event.ctx.mClient->getLocalPlayer();
		if (!player) return;


		auto modCount = Amethyst::GetContext().mModLoader->GetModCount();
		std::vector<std::string> texts = { std::format("Amethyst API ({} mod(s) loaded)\n", modCount) };

		// Position info
		texts.push_back(std::format("XYZ: {} {} {}\n", player->getPosition()->x, player->getPosition()->y, player->getPosition()->z));
		texts.push_back(std::format("Facing: {} ({})\n", yawToFacing(player->getHeadRot()->y), player->getHeadRot()->y));

		texts.push_back("\n");


		// Cursor info
		ILevel* level = client->getLocalPlayer()->getLevel();
		HitResult& hr = level->getHitResult();
		if (hr.mType == HitResultType::TILE) {
			auto& block = client->getRegion()->getBlock(hr.mBlock);
			texts.push_back(std::format("BlockPos: {} {} {}\n", hr.mBlock.x, hr.mBlock.y, hr.mBlock.z));
			texts.push_back(std::format("Block: {}:{}\n", block.mLegacyBlock->mNameInfo.mNamespaceName, block.mLegacyBlock->mNameInfo.mRawName.getString()));
		}

		texts.push_back("\n");

		// Dimension info 
		const Dimension& dimension = player->getDimensionConst();
		dimension.getId();
		texts.push_back("Dimension Info:\n");
		texts.push_back(std::format("dimension: {}\n", dimension.getId()));
		texts.push_back(std::format("dimension ID: {}\n", dimension.getId()));

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
			text += texts.at(i);
			if (texts.at(i).empty()) continue;
			auto mr = event.ctx.mMeasureStrategy.measureText(font, texts.at(i), 300, 300, textData, caretData);
			if(!(texts.at(i) == "\n"))
				event.ctx.fillRectangle(RectangleArea{ 0.0f, mr.mSize.x + 3.0f, ypos, ypos + mr.mSize.y}, mce::Color::FONT_DARK_GRAY, 0.5f);
			ypos += mr.mSize.y;
		}

		// Draw the text
		RectangleArea rect{ 2.0f, 100.0f, 2.0f, 700.0f };

		event.ctx.drawDebugText(rect, text, mce::Color::WHITE, 1.0f, ui::TextAlignment::Left, textData, caretData);
		event.ctx.flushText(0.0);
	}
}
#endif
