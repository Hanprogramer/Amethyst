#include "Environment.hpp"
#include <Windows.h>

const std::filesystem::path& Amethyst::GetExecutablePath()
{
    static const std::filesystem::path exePath = []() {
        wchar_t buffer[MAX_PATH];
        DWORD len = GetModuleFileNameW(NULL, buffer, MAX_PATH);
        if (len == 0) throw std::runtime_error("Failed to get executable path!");
        return std::filesystem::path(std::wstring(buffer, len));
    }();
    return exePath;
}

Amethyst::Environment Amethyst::GetEnvironment()
{
    static Amethyst::Environment env = []() {
        const auto& exePath = GetExecutablePath();
        std::string exeName = exePath.filename().generic_string();
        if (exeName.starts_with("bedrock_server")) {
            return Amethyst::Environment::Server;
        }
        else if (exeName.starts_with("Minecraft.Windows")) {
            return Amethyst::Environment::Client;
        }
        else {
            throw std::runtime_error(std::format("Unknown executable name: '{}' at '{}'!", exeName, exePath.generic_string()));
        }
    }();
    return env;
}
