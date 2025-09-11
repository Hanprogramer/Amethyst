#include "minecraft/src/common/locale/I18n.hpp"
#include <amethyst/Memory.hpp>

I18n& getI18n()
{
    using function = decltype(&getI18n);
    static auto func = std::bit_cast<function>(SigScan("48 83 EC ? BA ? ? ? ? 65 48 8B 04 25 ? ? ? ? 48 8B 08 8B 04 0A 39 05 ? ? ? ? 7F ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 75 ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 90 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 CC CC CC CC CC 48 89 5C 24"));
    return func();
}

std::string operator""_i18n(const char* str, size_t)
{
    return getI18n().get(str, nullptr);
}