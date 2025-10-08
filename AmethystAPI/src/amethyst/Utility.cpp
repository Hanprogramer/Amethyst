#include "amethyst/Utility.hpp"
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include <shlobj_core.h>
#include <filesystem>
#include <amethyst/Log.hpp>
#include <fstream>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "windows.h"

using namespace winrt;
using namespace Windows::Storage;

// fs::path GetComMojangPath()
// {
//     Assert(Amethyst::GetEnvironment() == Amethyst::Environment::Client, "GetComMojangPath can only be called in client environment");
//     StorageFolder localFolder = ApplicationData::Current().LocalFolder();
//     fs::path localPath = localFolder.Path().c_str();
//     return localPath / L"games" / L"com.mojang";
// }

// fs::path GetAmethystFolder()
// {
//     if (Amethyst::GetEnvironment() == Amethyst::Environment::Client)
//         return GetComMojangPath() / L"amethyst";
//     return Amethyst::GetExecutablePath().parent_path() / L"amethyst";
// }

std::string StringFromWstring(std::wstring wstring)
{
    return winrt::to_string(wstring);
}

std::wstring WstringFromString(std::string string)
{
    return winrt::to_hstring(string).data();
}

std::string ReadTextFile(const fs::path& filePath)
{
    std::ifstream file(filePath);
    Assert(file.is_open(), "Failed to open file '{}'", filePath.string());

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
