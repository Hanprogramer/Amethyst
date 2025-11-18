#pragma once
#include <amethyst/runtime/events/EventBus.hpp>
#include <mc/src-client/common/client/player/LocalPlayer.hpp>

class ScreenEvent;

class UIButtonHandleEvent : public BaseEvent {
public:
    ScreenEvent& mScreenEvent;

    UIButtonHandleEvent(ScreenEvent& screenEvent) 
        : mScreenEvent(screenEvent) {}
};

class F3DisplayEvent : public BaseEvent {
public:
	std::vector<std::string>& mLines;
	LocalPlayer& mPlayer;
	HitResult& mHitResult;

	F3DisplayEvent(std::vector<std::string>& lines, LocalPlayer& player, HitResult& hitResult) 
		: mLines(lines), mPlayer(player), mHitResult(hitResult) {
	}

	void AddLine(std::string newLine) {
		mLines.push_back(newLine);
	}
	void AddEmptyLine() { //
		mLines.push_back("");
	}
};

using UiButtonHandleEvent = UIButtonHandleEvent;