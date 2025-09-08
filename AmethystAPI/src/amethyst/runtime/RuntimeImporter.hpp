#pragma once
#include <string>
#include <unordered_map>

#define RUNTIME_IMPORT_VAR_DESC_TABLE ".rivdt"
#define RUNTIME_IMPORT_FUNC_DESC_TABLE ".rifdt"
#define RUNTIME_IMPORT_MANGLE_TABLE ".rimt"
#define RUNTIME_IMPORT_SIG_TABLE ".rist"
#define NEW_IMPORT_DIRECTORY ".idnew"

namespace Amethyst {
class RuntimeImporter {
public:
#pragma pack(push, 1)
    struct FunctionDescriptor {
        uint32_t nameIndex;
        uint32_t iatIndex;
        char isSignature;
        union {
            uint64_t signatureIndex;
            uint64_t address;
        };
    };

    struct VariableDescriptor {
        uint32_t nameIndex;
        uint32_t iatIndex;
        uint64_t address;
    };

    struct VariableDescriptorTable {
        uint32_t variableCount;
        uint32_t iatRva;
        uint32_t iatSize;
        VariableDescriptor variables;
    };

    struct FunctionDescriptorTable {
        uint32_t functionCount;
        uint32_t iatRva;
        uint32_t iatSize;
        FunctionDescriptor functions;
    };

    struct StringTable {
        uint32_t stringCount;
        char strings;
    };
#pragma pack(pop)

    static std::unordered_map<void*, std::unordered_map<std::string, uintptr_t*>> ImportAddresses;
    static std::unordered_map<void*, std::unordered_map<uint32_t, std::string>> IndexToImportName;
    static std::unordered_map<void*, std::unordered_map<uint32_t, std::string>> IndexToImportSignature;

    static bool LoadImports(void* handle);
    static bool UnloadImports(void* handle);
    static uintptr_t GetAddress(void* handle, const std::string& name);
    static uintptr_t* GetMutableAddress(void* handle, const std::string& name);
    static bool HasRuntimeImports(void* handle);
    static void UnloadedImportFallback();
};
}