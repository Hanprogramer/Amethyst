#pragma once
#include "platforms/WindowsPlatform.hpp"

class WindowsClientPlatform : public WindowsPlatform {
public:
    WindowsClientPlatform(HANDLE mcThreadHandle);

    virtual Amethyst::PlatformType GetPlatformType() const override;
    virtual fs::path GetComMojangPath() const override;
    virtual fs::path GetAmethystFolder() const override;
};