#pragma once
#include <string>
#include <unordered_map>
#include <Windows.h>
#include "amethyst-deps/safetyhook.hpp"

namespace Amethyst {
class RuntimeImporter {
private:
    HMODULE mModule = nullptr;
    bool mInitialized = false;

    std::unordered_map<uint32_t, std::string> mStringTable{};
    std::unordered_map<std::string, uintptr_t*> mImportAddressTable{};
    std::unordered_map<std::string, uintptr_t*> mFuntionImportAddresses{};
    std::unordered_map<std::string, uintptr_t> mVirtualTables{};
    std::unordered_map<std::string, uintptr_t> mVirtualDestructors{};
    std::unordered_map<std::string, safetyhook::Allocation> mAllocatedDestructorBlocks{};
    std::unordered_map<std::string, uintptr_t> mVtableToVarStorage{};
    std::shared_ptr<safetyhook::Allocator> mAllocator = nullptr;

public:
    RuntimeImporter(HMODULE moduleHandle);
    RuntimeImporter(const RuntimeImporter&) = delete;
    RuntimeImporter(RuntimeImporter&&) = delete;
    RuntimeImporter& operator=(const RuntimeImporter&) = delete;
    RuntimeImporter& operator=(RuntimeImporter&&) = delete;
    ~RuntimeImporter();

    bool IsInitialized() const;
    HMODULE GetModule() const;
    uintptr_t* GetMutableAddress(const std::string& name);
    uintptr_t GetAddress(const std::string& name) const;
    uintptr_t GetVirtualTableAddress(const std::string& name) const;

    void Initialize();
    void Shutdown();

    bool GetSections(
        IMAGE_SECTION_HEADER** stringTableSection,
        IMAGE_SECTION_HEADER** functionDescSection,
        IMAGE_SECTION_HEADER** virtualFunctionDescSection,
        IMAGE_SECTION_HEADER** variableDescSection,
        IMAGE_SECTION_HEADER** vtableDescSection) const;

    static void UninitializedFunctionHandler();
    static void UninitializedDestructorHandler();
    static bool IsDestructor(const std::string& name);
};
}; // namespace Amethyst