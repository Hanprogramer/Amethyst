#include "mc/src-client/common/client/input/RemappingLayout.hpp"

const Keymapping* RemappingLayout::getKeymappingByAction(const std::string& actionName) const {
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == actionName) return &keymapping;
    }

    return nullptr;
}

Keymapping* RemappingLayout::getKeymappingByAction(const std::string& actionName)
{
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == actionName) return &keymapping;
    }

    return nullptr;
}

int RemappingLayout::getAdjustedKey(int key) {
    using function = int(__thiscall*)(RemappingLayout*, int);
    return reinterpret_cast<function>((*reinterpret_cast<uintptr_t**>(this))[2])(this, key);
}   