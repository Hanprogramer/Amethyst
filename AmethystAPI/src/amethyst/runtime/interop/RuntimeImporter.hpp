#pragma once
#include <string>
#include <unordered_map>
#include "amethyst-deps/safetyhook.hpp"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace Amethyst {
class RuntimeImporter : 
    std::enable_shared_from_this<RuntimeImporter> 
{
private:
    static std::unordered_map<HMODULE, RuntimeImporter*> sImporters;

    HMODULE mModule = nullptr;
    bool mInitialized = false;
    explicit RuntimeImporter(HMODULE moduleHandle);
public:
    RuntimeImporter(const RuntimeImporter&) = delete;
    RuntimeImporter(RuntimeImporter&&) = delete;
    RuntimeImporter& operator=(const RuntimeImporter&) = delete;
    RuntimeImporter& operator=(RuntimeImporter&&) = delete;
    ~RuntimeImporter();

    bool ResolveAll() const;

    static void UninitializedFunctionHandler();
    static void UninitializedDestructorHandler();
    static bool IsDestructor(const std::string& name);
    static bool HasImporter(HMODULE moduleHandle);
    static std::shared_ptr<RuntimeImporter> GetImporter(HMODULE moduleHandle);
};
}; // namespace Amethyst