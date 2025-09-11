#pragma once
#include <string>
#include <unordered_map>
#include <Windows.h>

namespace Amethyst {
class RuntimeImporter {
public:
#pragma pack(push, 1)
    struct StringTable {
        uint32_t length;
        char strings;
    };

    struct FunctionDesc {
        uint32_t nameIndex;
        uint32_t iatIndex;
        char usesSig;
        union {
            uint64_t signatureIndex;
            uint64_t address;
        };
    };

    struct FunctionDescTable {
        uint32_t length;
        uint32_t iatRva;
        uint32_t iatSize;
        FunctionDesc entries;
    };

    struct VariableDesc {
        uint32_t nameIndex;
        uint32_t iatIndex;
        uint64_t address;
    };

    struct VariableDescTable {
        uint32_t length;
        uint32_t iatRva;
        uint32_t iatSize;
        VariableDesc entries;
    };

    struct VirtualTableDesc {
        uint32_t nameIndex;
        uint64_t address;
    };

    struct VirtualTableDescTable {
        uint32_t length;
        VirtualTableDesc entries;
    };

    struct VirtualFunctionDesc {
        uint32_t nameIndex;
        uint32_t iatIndex;
        uint32_t vtableNameIndex;
        uint32_t functionIndex;
    };

    struct VirtualFunctionDescTable {
        uint32_t length;
        uint32_t iatRva;
        uint32_t iatSize;
        VirtualFunctionDesc entries;
    };
#pragma pack(pop)

    static constexpr const char* StringTableSectionName = ".strt";
    static constexpr const char* FunctionDescSectionName = ".fndt";
    static constexpr const char* VirtualFunctionDescSectionName = ".vfndt";
    static constexpr const char* VariableDescSectionName = ".vardt";
    static constexpr const char* VtableDescSectionName = ".vtbdt";

private:
    HMODULE mModule = nullptr;
    bool mInitialized = false;

    std::unordered_map<uint32_t, std::string> mStringTable{};
    std::unordered_map<std::string, uintptr_t*> mImportAddressTable{};
    std::unordered_map<std::string, uintptr_t> mVirtualTables{};

public:
    RuntimeImporter(HMODULE moduleHandle);
    ~RuntimeImporter();

    bool IsInitialized() const;
    HMODULE GetModule() const;
    uintptr_t* GetAddress(const std::string& name);
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
};
}; // namespace Amethyst