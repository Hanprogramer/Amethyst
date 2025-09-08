#include "minecraft/src-client/common/client/gui/screens/ScreenController.hpp"
#include "amethyst/Memory.hpp"
#include "amethyst/Utility.hpp"

void ScreenController::bindString(const StringHash& bindingName, const std::function<std::string()>& callback, const std::function<bool()>& condition)
{
    using function = decltype(&ScreenController::bindString);
    static auto func = std::bit_cast<function>(SigScan(""));
    (this->*func)(bindingName, callback, condition);
}