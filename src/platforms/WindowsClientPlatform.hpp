#pragma once
#include "platforms/WindowsPlatformCommon.hpp"

class WindowsClientPlatform : public WindowsPlatformCommon {
public:
    WindowsClientPlatform(HANDLE mcThreadHandle);

    virtual Amethyst::PlatformType GetPlatformType() const override;
    virtual fs::path GetComMojangPath() const override;
    virtual fs::path GetAmethystFolder() const override;
};