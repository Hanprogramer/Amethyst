#include "WindowsClientPlatform.hpp"
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "windows.h"

using namespace winrt;
using namespace Windows::Storage;


fs::path WindowsClientPlatform::GetComMojangPath() const
{
    StorageFolder localFolder = ApplicationData::Current().LocalFolder();
    fs::path localPath = localFolder.Path().c_str();
    return localPath / "games" / "com.mojang";
}

fs::path WindowsClientPlatform::GetAmethystFolder() const
{
    return GetComMojangPath() / "amethyst";
}