#include "Mod.hpp"
#include <fstream>

namespace Amethyst {
Mod::Mod(const std::string& modName) : 
    info(GetInfo(modName))
{
    fs::path dllPath = GetTemporaryLibrary(modName);

    // Loads the mod in a temporary directory so that the original DLL can still be built to
    hModule = LoadLibrary(dllPath.string().c_str());
    if (hModule == NULL) {
        DWORD error = GetLastError();

        switch (error) {
        case ERROR_ACCESS_DENIED:
            Assert(false, "'{}' does not have the required privileges!", dllPath.string());
            break;
        case ERROR_MOD_NOT_FOUND:
            Assert(false, "Failed to find '{}'", dllPath.string());
            break;
        default:
            Assert(false, "Failed to load '{}.dll', error code: 0x{:x}", modName, error);
            break;
        }
    }
}

Mod::Mod(const std::string& modInfo, HMODULE moduleHandle) : 
    Mod(modInfo)
{
    hModule = moduleHandle;
}

Mod::Mod(Mod&& other) noexcept :
    info(other.info),
    mRuntimeImporter(std::move(other.mRuntimeImporter)),
    hModule(std::exchange(other.hModule, nullptr))
{
}

Mod::~Mod()
{
    mRuntimeImporter.reset();
    FreeLibrary(hModule);
}

HMODULE Mod::GetModule() const
{
    return hModule;
}

Amethyst::RuntimeImporter& Mod::GetRuntimeImporter() const
{
    return *mRuntimeImporter;
}

bool Mod::operator==(const Mod& other) const
{
    return info == other.info;
}

Mod::Info Amethyst::Mod::GetInfo(const std::string& modName)
{
    // Ensure the mod exists
    fs::path modConfigPath = GetAmethystFolder() / L"mods" / modName / L"mod.json";
    Assert(fs::exists(modConfigPath), "mod.json could not be found, for '{}'", modName);

    // Try to read it to a std::string
    std::ifstream modConfigFile(modConfigPath);

    Assert(modConfigFile.is_open(), "Failed to open mod.json, for '{}'", modName);

    // Read into a std::string
    std::stringstream buffer;
    buffer << modConfigFile.rdbuf();
    modConfigFile.close();
    std::string fileContents = buffer.str();

    return Mod::Info::FromJson(fileContents);
}

fs::path Mod::GetTemporaryLibrary(const std::string& modName)
{
    std::string modShortened = modName;
    size_t atPos = modShortened.find("@");

    if (atPos != std::string::npos) {
        modShortened = modShortened.substr(0, atPos);
    }

    // Ensure temp directory exists
    fs::path tempDir = GetAmethystFolder() / L"Temp" / modName;
    if (!fs::exists(tempDir)) fs::create_directories(tempDir);

    fs::path originalDll = GetAmethystFolder() / L"Mods" / modName / std::string(modShortened + ".dll");
    Assert(fs::exists(originalDll), "Could not find '{}.dll'", modShortened);

    fs::path tempDll = tempDir.string() + modShortened + ".dll";

    try {
        fs::copy_file(originalDll, tempDll, fs::copy_options::overwrite_existing);
    }
    catch (const std::filesystem::filesystem_error& e) {
        Assert(false, "{} (Error code: {})", e.what(), e.code().value());
    }

    return tempDll;
}
} // namespace Amethyst