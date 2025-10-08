#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/*
Returns a path to Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalState/games/com.mojang
*/
fs::path GetComMojangPath();

/*
 * Returns a path to the /amethyst folder
 * In client this is com.mojang/amethyst
 * In server this is next to the server executable (e.g. server_root/amethyst)
 */
fs::path GetAmethystFolder();


std::string StringFromWstring(std::wstring wstring);
std::wstring WstringFromString(std::string string);

std::string ReadTextFile(const fs::path& filePath);