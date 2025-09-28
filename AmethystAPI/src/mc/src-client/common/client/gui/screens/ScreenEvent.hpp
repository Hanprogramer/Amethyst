#pragma once
#include <cstdint>
#include <mc/src-deps/input/InputMode.hpp>
#include <mc/src-deps/input/InputHandler.hpp>

class UIPropertyBag;

enum class ScreenEventType : int32_t {
    Undefined = 0x0000,
    ButtonEvent = 0x0001,
    ButtonMoveEvent = 0x0002,
    PointerMoveInEvent = 0x0003,
    PointerMoveOutEvent = 0x0004,
    HoverEvent = 0x0005,
    PointerMoveEvent = 0x0006,
    PointerHeldEvent = 0x0007,
    FocusMoveEvent = 0x0008,
    PreCollectionRefresh = 0x0009,
    InputModeChangeEvent = 0x000a,
    HoloInputModeChangeEvent = 0x000b,
    ScreenViewRefresh = 0x000c,
    ScrollDirectionEvent = 0x000d,
    ScrollRequestEvent = 0x000e,
    TextEditChange = 0x000f,
    ToggleChangeEvent = 0x0010,
    ControllerDirectionEvent = 0x0011,
    RawInputEvent = 0x0012,
    SliderChangeEvent = 0x0013,
    AnimationEvent = 0x0014,
    LockedStateEvent = 0x0015,
    ClippedCollectionRange = 0x0016,
    ClipStateChangeEvent = 0x0017,
    TextEditSelectedStateChangeEvent = 0x0018,
    CustomRendererEvent = 0x0019,
    ScreenEventTypeCount = 0x001a,
};

struct ButtonScreenEventData {
public:
    uint32_t id;
    uint32_t fromButtonId;
    ButtonState previousState;
    ButtonState state;
    bool handleDeselection;
    bool handleSelection;
    UIPropertyBag* properties;
    float cursorPosition[2];
    bool isInteracted;
    InputMode inputMode;
};

union ScreenEventData {
    ButtonScreenEventData button;
    //TextEditScreenEventData textEdit;
    //HoverScreenEventData hover;
    //PointerMoveScreenEventData pointerMove;
    //PointerHeldScreenEventData pointerHeld;
    //FocusMoveScreenEventData focusMove;
    //InputModeChangeScreenEventData inputMode;
    //HoloInputModeChangeScreenEventData holoInputMode;
    //ScrollRequestScreenEventData scrollRequest;
    //ScrollDirectionEventData scrollDirectionRequest;
    //ToggleChangeEventData toggle;
    //ControllerDirectionEventData controllerDirectionEventData;
    //RawInputScreenEventData rawInput;
    //SliderChangeEventData slider;
    //AnimationEventData animEventData;
    //LockedStateEventData locked;
    //ClippedCollectionEventData clippedCollection;
    //ClipStateChangeEventData clipStateChangeEventData;
    //TextEditSelectedStateChangeEventData textEditSelectedStateChangeEventData;
    //CustomRendererEventData customRendererEventData;
};

enum class ScreenEventScope : char {
  Controller = 0x0000,
  View = 0x0001,
};

class ScreenEvent {
public:
    ScreenEventType type;
    ScreenEventData data;
    ScreenEventScope scope;
    bool localEvent;
};