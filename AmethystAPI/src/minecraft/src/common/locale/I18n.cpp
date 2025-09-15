#include "minecraft/src/common/locale/I18n.hpp"
#include <amethyst/Memory.hpp>

std::string operator""_i18n(const char* str, size_t)
{
    return getI18n().get(str, nullptr);
}