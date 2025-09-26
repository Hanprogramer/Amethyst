#include "Mod.hpp"
#include <fstream>

namespace Amethyst {
Mod::Mod(const std::shared_ptr<const ModInfo>& info) : 
    mInfo(info)
{
}

Mod::Mod(Mod&& other) noexcept :
    mInfo(std::move(other.mInfo)),
    mRuntimeImporter(std::move(other.mRuntimeImporter)),
    mHandle(std::move(other.mHandle)),
    mIsLoaded(std::move(other.mIsLoaded))
{
}

Mod::~Mod()
{
    if (IsLoaded())
        Unload();

    mRuntimeImporter.reset();
}

void Mod::Load()
{
    if (IsLoaded())
        return;

    std::string versionedName = mInfo->GetVersionedName();
    fs::path dllPath = mInfo->Directory / mInfo->LibraryName;

    // Loads the mod in a temporary directory if it's not a runtime so that the original DLL can still be built to
    if (!mInfo->IsRuntime)
        dllPath = GetTemporaryLibrary(versionedName);

    HMODULE handle = LoadLibrary(dllPath.string().c_str());

    mHandle.Reset(handle);
    if (!mHandle) {
        DWORD error = GetLastError();

        switch (error) {
        case ERROR_ACCESS_DENIED:
            Assert(false, "'{}' does not have the required privileges!", dllPath.string());
            break;
        case ERROR_MOD_NOT_FOUND:
            Assert(false, "Failed to find '{}'", dllPath.string());
            break;
        default:
            Assert(false, "Failed to load '{}.dll', error code: 0x{:x}", versionedName, error);
            break;
        }
    }

    Assert(mHandle, "Module handle cannot be null");
    mRuntimeImporter = RuntimeImporter::GetImporter(mHandle);

    Assert(mRuntimeImporter != nullptr, "Failed to get runtime importer for '{}'", versionedName);
    mRuntimeImporter->Initialize();
    mIsLoaded = true;
}

void Mod::Unload()
{
    if (!IsLoaded())
        return;

    if (mRuntimeImporter) {
        mRuntimeImporter->Shutdown();
    }
    mRuntimeImporter.reset();
    mHandle.Reset();
    mIsLoaded = false;
}

void Mod::Attach(HMODULE moduleHandle)
{
    if (IsLoaded())
        Unload();

    mHandle.Reset(moduleHandle);
    mRuntimeImporter = RuntimeImporter::GetImporter(moduleHandle);
    mRuntimeImporter->Initialize();
    mIsLoaded = true;
}

const ModuleHandle& Mod::GetHandle() const
{
    return mHandle;
}

Amethyst::RuntimeImporter& Mod::GetRuntimeImporter() const
{
    return *mRuntimeImporter;
}

Mod::InitializeFunction Mod::GetInitializeFunction()
{
    if (mInitializeFunction != nullptr)
        return mInitializeFunction;
    mInitializeFunction = GetFunction<InitializeFunction>("Initialize");
    return mInitializeFunction;
}

Mod::ShutdownFunction Mod::GetShutdownFunction()
{
    if (mShutdownFunction != nullptr)
        return mShutdownFunction;
    mShutdownFunction = GetFunction<ShutdownFunction>("Shutdown");
    return mShutdownFunction;
}

void Mod::CallInitialize(AmethystContext& ctx, const Mod& mod)
{
    if (mIsInitialized)
        return;
    auto initFunc = GetInitializeFunction();
    if (initFunc != nullptr) {
        initFunc(ctx, mod);
        mIsInitialized = true;
    }
}

void Mod::CallShutdown(AmethystContext& ctx, const Mod& mod)
{
    if (!mIsInitialized)
        return;
    auto shutdownFunc = GetShutdownFunction();
    if (shutdownFunc != nullptr) {
        shutdownFunc(ctx, mod);
        mIsInitialized = false;
    }
}

bool Mod::IsLoaded() const
{
    return mIsLoaded;
}

bool Mod::operator==(const Mod& other) const
{
    return mInfo == other.mInfo;
}

std::shared_ptr<const ModInfo> Amethyst::Mod::GetInfo(const std::string& modName)
{
    fs::path modConfigPath = GetAmethystFolder() / L"mods" / modName / L"mod.json";
    Assert(fs::exists(modConfigPath), "mod.json could not be found, for '{}'", modName);
    auto result = ModInfo::FromFile(modConfigPath);
    if (!result.has_value())
        Assert(result.has_value(), "Failed to read mod info for '{}': {}", modName, result.error().toString());
    return std::make_shared<const Amethyst::ModInfo>(std::move(*result));
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