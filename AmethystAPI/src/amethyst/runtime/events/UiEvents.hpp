#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ScreenEvent;

class UiButtonHandleEvent : public BaseEvent {
public:
    ScreenEvent& mScreenEvent;

    UiButtonHandleEvent(ScreenEvent& screenEvent) 
        : mScreenEvent(screenEvent) {}
};