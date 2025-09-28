#pragma once
#include <vector>
#include <memory>
#include <mc/src-client/common/client/input/RemappingLayout.hpp>

using KeyboardRemappingLayout = RemappingLayout;

class Options {
public:
    /* this + 0    */ std::byte padding0[6256];
    /* this + 6256 */ std::vector<std::shared_ptr<KeyboardRemappingLayout>> mKeyboardRemappings;

    void* _readKeyboardMapping(char* a2, char* a3);
};