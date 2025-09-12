/// @symbolgeneration
#pragma once
#include "minecraft/src-deps/core/string/StringHash.hpp"
#include <amethyst/Imports.hpp>

namespace ui {
enum class ViewRequest : uint32_t {
    None = 0x0000,
    Refresh = 0x0001,
    PointerHeldEventsRequest = 0x0002,
    PointerHeldEventsCancel = 0x0004,
    DelayedFocusRefresh = 0x0008,
    Exit = 0x0010,
    ConsumeEvent = 0x0020,
};
}

class UiPropertyBag;
class ScreenEvent;


class ScreenController {
public:
    /// @signature {89 54 24 ? 55 53 56 57 41 56 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0 8B DA 4C 8B C9 4C 89 45 ? 48 8D B9 ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 48 B9 ? ? ? ? ? ? ? ? 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 49 8B 89 ? ? ? ? 49 23 C8 48 C1 E1 ? 49 8B 81 ? ? ? ? 48 03 C1 48 8B 48 ? 49 8B 91 ? ? ? ? 45 33 F6 48 3B CA 74 ? 48 8B 00 3B 59 ? 74 ? 48 3B C8 74 ? 48 8B 49 ? 3B 59 ? 75 ? EB ? 49 8B CE 48 85 C9 48 0F 44 CA 48 3B CA 74 ? 48 83 C1 ? 48 8B D6 E8 ? ? ? ? E9 ? ? ? ? 0F 57 C9 F3 0F 7F 4D ? 4C 89 75 ? 4C 8B C6 33 D2 48 8D 4D ? E8 ? ? ? ? 89 5D ? 4C 8B 45 ? 4C 89 75 ? 48 8B 55 ? 4C 89 75 ? 48 8B 45 ? 4C 89 75 ? 48 89 45 ? 48 89 55 ? 4C 89 45 ? 4C 8D 45 ? 48 8D 55 ? 48 8B CF E8 ? ? ? ? 90 48 8D 4D ? E8 ? ? ? ? 90 48 8B 5D ? 48 85 DB 74 ? 48 8B 7D ? 48 3B DF 74 ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 73 ? 48 83 C3 ? 48 3B DF 75 ? 48 8B 5D ? 48 8B 55 ? 48 2B D3 48 83 E2 ? 48 8B C3 48 81 FA ? ? ? ? 72 ? 48 83 C2 ? 48 8B 5B ? 48 2B C3 48 83 C0 ? 48 83 F8 ? 76 ? FF 15 ? ? ? ? CC 48 8B CB E8 ? ? ? ? 90 48 8B 4E ? 48 85 C9 74 ? 48 8B 01 48 3B CE 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 76 ? 48 8B 4D ? 48 33 CC E8 ? ? ? ? 48 81 C4 ? ? ? ? 41 5E 5F 5E 5B 5D C3 CC CC CC CC CC CC CC 48 89 5C 24 ? 57}
    MC void registerButtonInteractedHandler(uint32_t id, std::function<ui::ViewRequest(UiPropertyBag*)> callback);

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 10 52}
    MC ui::ViewRequest _handleButtonEvent(ScreenEvent& event);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B DA 48 8B F9 48 8B 49 ? 48 85 C9 75}
    MC void bindString(const StringHash& bindingName, const std::function<std::string()>& callback, const std::function<bool()>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B B4 24 ? ? ? ? 48 8B F9 48 8B 49 ? 49 8B D9 44 89 44 24 ? 41 8B F0 48 8B EA 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B 40 ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B 4F ? 89 74 24 ? 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B D5 48 8B 40 ? FF 15 ? ? ? ? 48 83 7B ? ? 89 44 24}
    MC void bindIntForAnyCollection(const StringHash& bindingName, const std::function<int(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 6B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D9 49 8B F8 48 8B F2 48 8D A9 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 48 8B 84 24 ? ? ? ? 48 8B 48 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 06 33 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CD E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 6B ? 49 8B 73 ? 49 8B E3 5F C3 CC 48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B F9}
    MC void bindIntForCollection(const StringHash& bindingName, const std::string& collectionName, const std::function<int(int index)>& callback, const std::function<bool(int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B D9 41 8B E8}
    MC void bindBoolForAnyCollection(const StringHash& bindingName, const std::function<bool(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B B4 24 ? ? ? ? 48 8B F9 48 8B 49 ? 49 8B D9 44 89 44 24 ? 41 8B F0 48 8B EA 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B 40 ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B 4F ? 89 74 24 ? 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B D5 48 8B 40 ? FF 15 ? ? ? ? 48 83 7B ? ? 48 8B C3}
    MC void bindFloatForAnyCollection(const StringHash& bindingName, const std::function<float(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);
};