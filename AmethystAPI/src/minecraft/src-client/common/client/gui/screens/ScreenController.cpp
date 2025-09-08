#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"
#include "amethyst/Memory.hpp"
#include "amethyst/Utility.hpp"

void ScreenController::bindString(const StringHash& bindingName, const std::function<std::string()>& callback, const std::function<bool()>& condition)
{
    using function = decltype(&ScreenController::bindString);
    static auto func = std::bit_cast<function>(SigScan(""));
    (this->*func)(bindingName, callback, condition);
}

void ScreenController::registerButtonInteractedHandler(uint32_t id, std::function<ui::ViewRequest(UiPropertyBag*)> callback)
{
    using function = decltype(&ScreenController::registerButtonInteractedHandler);
    static auto func = std::bit_cast<function>(SigScan("89 54 24 ? 55 53 56 57 41 56 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0 8B DA 4C 8B C9 4C 89 45 ? 48 8D B9 ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 48 B9 ? ? ? ? ? ? ? ? 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 49 8B 89 ? ? ? ? 49 23 C8 48 C1 E1 ? 49 8B 81 ? ? ? ? 48 03 C1 48 8B 48 ? 49 8B 91 ? ? ? ? 45 33 F6 48 3B CA 74 ? 48 8B 00 3B 59 ? 74 ? 48 3B C8 74 ? 48 8B 49 ? 3B 59 ? 75 ? EB ? 49 8B CE 48 85 C9 48 0F 44 CA 48 3B CA 74 ? 48 83 C1 ? 48 8B D6 E8 ? ? ? ? E9 ? ? ? ? 0F 57 C9 F3 0F 7F 4D ? 4C 89 75 ? 4C 8B C6 33 D2 48 8D 4D ? E8 ? ? ? ? 89 5D ? 4C 8B 45 ? 4C 89 75 ? 48 8B 55 ? 4C 89 75 ? 48 8B 45 ? 4C 89 75 ? 48 89 45 ? 48 89 55 ? 4C 89 45 ? 4C 8D 45 ? 48 8D 55 ? 48 8B CF E8 ? ? ? ? 90 48 8D 4D ? E8 ? ? ? ? 90 48 8B 5D ? 48 85 DB 74 ? 48 8B 7D ? 48 3B DF 74 ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 73 ? 48 83 C3 ? 48 3B DF 75 ? 48 8B 5D ? 48 8B 55 ? 48 2B D3 48 83 E2 ? 48 8B C3 48 81 FA ? ? ? ? 72 ? 48 83 C2 ? 48 8B 5B ? 48 2B C3 48 83 C0 ? 48 83 F8 ? 76 ? FF 15 ? ? ? ? CC 48 8B CB E8 ? ? ? ? 90 48 8B 4E ? 48 85 C9 74 ? 48 8B 01 48 3B CE 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 76 ? 48 8B 4D ? 48 33 CC E8 ? ? ? ? 48 81 C4 ? ? ? ? 41 5E 5F 5E 5B 5D C3 CC CC CC CC CC CC CC 48 89 5C 24 ? 57"));
    (this->*func)(id, callback);
}
