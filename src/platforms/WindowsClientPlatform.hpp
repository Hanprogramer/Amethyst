#pragma once
#include "platforms/WindowsPlatform.hpp"

class WindowsClientPlatform : public WindowsPlatform {
public:
    virtual fs::path GetComMojangPath() const override;
    virtual fs::path GetAmethystFolder() const override;
};