#include <amethyst/runtime/interop/RuntimeImporter.hpp>
#include <amethyst/Log.hpp>
#include <amethyst/Memory.hpp>
#include "minecraft/src-client/common/client/world/WorldCreationHelper.hpp"

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
static constexpr const uint8_t VirtualDestructorDeletingDisableBlock[] = {
    0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // mov rax, 0x1000000000000000
    0x30, 0xD2,                                                 // xor dl, dl (sets delete flag to false)
    0xFF, 0xE0                                                  // jmp rax
};

Amethyst::RuntimeImporter::RuntimeImporter(HMODULE moduleHandle) : 
	mModule(moduleHandle),
    mInitialized(false),
    mAllocator(safetyhook::Allocator::create())
{
}

Amethyst::RuntimeImporter::~RuntimeImporter()
{
    Shutdown();
}

bool Amethyst::RuntimeImporter::IsInitialized() const
{
    return mInitialized;
}

HMODULE Amethyst::RuntimeImporter::GetModule() const
{
    return mModule;
}

uintptr_t* Amethyst::RuntimeImporter::GetMutableAddress(const std::string& name)
{
    if (mImportAddressTable.count(name) == 0)
        return nullptr;
    return mImportAddressTable[name];
}

uintptr_t Amethyst::RuntimeImporter::GetAddress(const std::string& name) const
{
    if (IsDestructor(name)) {
        auto it = mVirtualDestructors.find(name);
        if (it != mVirtualDestructors.end()) {
            return it->second;
        }
    }

    if (mImportAddressTable.count(name) == 0)
        return 0x0;
    return *mImportAddressTable.find(name)->second;
}

bool Amethyst::RuntimeImporter::IsDestructor(const std::string& name)
{
    return name.starts_with("??1") || name.starts_with("?_G") || name.starts_with("?_E");
}

uintptr_t Amethyst::RuntimeImporter::GetVirtualTableAddress(const std::string& name) const
{
    if (mVirtualTables.count(name) == 0)
        return 0x0;
    return mVirtualTables.find(name)->second;
}

void Amethyst::RuntimeImporter::Initialize()
{
    if (mInitialized) {
        return;
    }

    if (mModule == nullptr) {
        Log::Error("[RuntimeImporter] Module handle is null, cannot initialize!");
        return;
    }

    IMAGE_SECTION_HEADER
        *stringTableSection,
        *functionDescSection,
        *virtualFunctionDescSection,
        *variableDescSection,
        *vtableDescSection;

    // Try to get all sections
    if (!GetSections(
        &stringTableSection, 
        &functionDescSection, 
        &virtualFunctionDescSection,
        &variableDescSection, 
        &vtableDescSection)) 
    {
        Log::Warning("[RuntimeImporter] Failed to find required sections in module, cannot initialize.");
        return;
    }

    uintptr_t base = reinterpret_cast<uintptr_t>(mModule);

    mStringTable.clear();
    // Construct string table
    {
        StringTable& stringTable = *reinterpret_cast<StringTable*>(base + stringTableSection->VirtualAddress);
        const char* string = &stringTable.strings;
        for (auto i = 0; i < stringTable.length; i++) {
            std::string str = string;
            string += str.length() + 1; // +1 for null-terminator
            mStringTable[i] = str;
        }
    }

    mImportAddressTable.clear();
    // Parse and initialize the function descriptor table
    {
        FunctionDescTable& functionDescTable = *reinterpret_cast<FunctionDescTable*>(base + functionDescSection->VirtualAddress);
        FunctionDesc* functionDesc = &functionDescTable.entries;
        uintptr_t* iat = reinterpret_cast<uintptr_t*>(base + functionDescTable.iatRva);
        UnprotectMemory(reinterpret_cast<uintptr_t>(iat), functionDescTable.iatSize, nullptr);
        for (auto i = 0; i < functionDescTable.length; i++, functionDesc++) {
            uintptr_t& address = iat[functionDesc->iatIndex];
            address = reinterpret_cast<uintptr_t>(&UninitializedFunctionHandler);
            auto nameIt = mStringTable.find(functionDesc->nameIndex);
            if (nameIt == mStringTable.end()) {
                Log::Warning("[RuntimeImporter] Function descriptor has invalid name index: {}", functionDesc->nameIndex);
                continue;
            }

            std::string& name = nameIt->second;
            if (functionDesc->usesSig) {
                auto sigIt = mStringTable.find(static_cast<uint32_t>(functionDesc->signatureIndex));
                if (sigIt == mStringTable.end()) {
                    Log::Warning("[RuntimeImporter] Function descriptor '{}' has invalid signature index: {}", name, functionDesc->signatureIndex);
                    address = reinterpret_cast<uintptr_t>(&UninitializedFunctionHandler);
                    continue;
                }

                std::string& signature = sigIt->second;
                auto resolvedAddress = SigScanSafe(signature);
                if (!resolvedAddress.has_value()) {
                    Log::Warning("[RuntimeImporter] Failed to resolve signature for function '{}': {}", name, signature);
                    address = reinterpret_cast<uintptr_t>(&UninitializedFunctionHandler);
                    continue;
                }
                address = resolvedAddress.value();
            }
            else {
                address = static_cast<uintptr_t>(SlideAddress(functionDesc->address));
            }
            mImportAddressTable[name] = &address;
            mFuntionImportAddresses[name] = &address;
        }
    }

    mVtableToVarStorage.clear();
    // Parse and initialize the variable descriptor table
    {
        VariableDescTable& variableDescTable = *reinterpret_cast<VariableDescTable*>(base + variableDescSection->VirtualAddress);
        VariableDesc* variableDesc = &variableDescTable.entries;
        uintptr_t* iat = reinterpret_cast<uintptr_t*>(base + variableDescTable.iatRva);
        UnprotectMemory(reinterpret_cast<uintptr_t>(iat), variableDescTable.iatSize, nullptr);
        for (auto i = 0; i < variableDescTable.length; i++, variableDesc++) {
            uintptr_t& address = iat[variableDesc->iatIndex];
            address = 0x0;
            auto nameIt = mStringTable.find(variableDesc->nameIndex);
            if (nameIt == mStringTable.end()) {
                Log::Warning("[RuntimeImporter] Variable descriptor has invalid name index: {}", variableDesc->nameIndex);
                continue;
            }

            std::string& name = nameIt->second;
            if (name.starts_with("?$vtable_for_")) {
                mVtableToVarStorage[name] = SlideAddress(variableDesc->address);
                address = reinterpret_cast<uintptr_t>(&mVtableToVarStorage[name]);
            }
            else {
                address = SlideAddress(variableDesc->address);
            }
            
            mImportAddressTable[name] = &address;
        }
    }

    mVirtualTables.clear();
    // Parse and initialize the virtual tables
    {
        VirtualTableDescTable& virtualTableDescTable = *reinterpret_cast<VirtualTableDescTable*>(base + vtableDescSection->VirtualAddress);
        VirtualTableDesc* virtualTableDesc = &virtualTableDescTable.entries;
        for (auto i = 0; i < virtualTableDescTable.length; i++, virtualTableDesc++) {
            auto nameIt = mStringTable.find(virtualTableDesc->nameIndex);
            if (nameIt == mStringTable.end()) {
                Log::Warning("[RuntimeImporter] Virtual table descriptor has invalid name index: {}", virtualTableDesc->nameIndex);
                continue;
            }

            std::string& name = nameIt->second;
            if (virtualTableDesc->address == 0x0) {
                Log::Warning("[RuntimeImporter] Virtual table '{}' has nullptr address, keep in mind this will probably cause BIG problems.", name);
            }

            mVirtualTables[name] = SlideAddress(virtualTableDesc->address);
        }
    }

    // Parse and initialize the virtual function descriptor table
    {
        VirtualFunctionDescTable& virtualFunctionDescTable = *reinterpret_cast<VirtualFunctionDescTable*>(base + virtualFunctionDescSection->VirtualAddress);
        VirtualFunctionDesc* virtualFunctionDesc = &virtualFunctionDescTable.entries;
        uintptr_t* iat = reinterpret_cast<uintptr_t*>(base + virtualFunctionDescTable.iatRva);
        UnprotectMemory(reinterpret_cast<uintptr_t>(iat), virtualFunctionDescTable.iatSize, nullptr);
        for (auto i = 0; i < virtualFunctionDescTable.length; i++, virtualFunctionDesc++) {
            uintptr_t& address = iat[virtualFunctionDesc->iatIndex];
            address = reinterpret_cast<uintptr_t>(&UninitializedFunctionHandler);
            auto nameIt = mStringTable.find(virtualFunctionDesc->nameIndex);
            if (nameIt == mStringTable.end()) {
                Log::Warning("[RuntimeImporter] Virtual function descriptor has invalid name index: {}", virtualFunctionDesc->nameIndex);
                continue;
            }

            std::string& name = nameIt->second;
            auto vtableNameIt = mStringTable.find(virtualFunctionDesc->vtableNameIndex);
            if (vtableNameIt == mStringTable.end()) {
                Log::Warning("[RuntimeImporter] Virtual function descriptor for '{}' has invalid virtual table name index: {}", name, virtualFunctionDesc->vtableNameIndex);
                continue;
            }

            std::string vtableName = vtableNameIt->second;
            uintptr_t vtableAddress = mVirtualTables[vtableName];
            uintptr_t vfuncAddress = reinterpret_cast<uintptr_t*>(vtableAddress)[virtualFunctionDesc->functionIndex];
            
            // If this is a destructor, we need to wrap it in a special block that disables deleting
            if (IsDestructor(name)) {
                mVirtualDestructors[vtableName] = vfuncAddress;
                auto allocationExp = mAllocator->allocate(sizeof(VirtualDestructorDeletingDisableBlock));
                
                if (!allocationExp.has_value()) {
                    Log::Warning("[RuntimeImporter] Failed to allocate memory of virtual destructor block for '{}'", name);
                    address = reinterpret_cast<uintptr_t>(&UninitializedDestructorHandler);
                    continue;
                }

                auto& allocation = (mAllocatedDestructorBlocks[name] = std::move(*allocationExp));
                uint8_t* block = allocation.data();
                std::memcpy(block, VirtualDestructorDeletingDisableBlock, sizeof(VirtualDestructorDeletingDisableBlock));
                uint64_t& addrInBlock = *reinterpret_cast<uint64_t*>(block + 2);
                addrInBlock = vfuncAddress;
                vfuncAddress = reinterpret_cast<uintptr_t>(block);
            }

            address = vfuncAddress;
            mImportAddressTable[name] = &address;
            mFuntionImportAddresses[name] = &address;
        }
    }

    mInitialized = true;
}

void Amethyst::RuntimeImporter::Shutdown()
{
    if (!mInitialized) {
        return;
    }

    for (auto& [name, address] : mFuntionImportAddresses) {
        (*address) = reinterpret_cast<uintptr_t>(&UninitializedFunctionHandler);
    }
    mStringTable.clear();
    mFuntionImportAddresses.clear();
    mImportAddressTable.clear();
    mVirtualTables.clear();
    mVirtualDestructors.clear();
    mAllocatedDestructorBlocks.clear();
    mVtableToVarStorage.clear();
    mInitialized = false;
}

bool Amethyst::RuntimeImporter::GetSections(
    IMAGE_SECTION_HEADER** stringTableSection,
    IMAGE_SECTION_HEADER** functionDescSection,
    IMAGE_SECTION_HEADER** virtualFunctionDescSection,
    IMAGE_SECTION_HEADER** variableDescSection,
    IMAGE_SECTION_HEADER** vtableDescSection
) const
{
    uintptr_t base = reinterpret_cast<uintptr_t>(mModule);

    // Grab the ancient DOS header
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        Log::Error("[RuntimeImporter] DOS header signature is NOT 'MZ'...");
        Log::Error("[RuntimeImporter] What the fuck did you do to make this happen?");
        return false;
    }

    // Jump to NT headers
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    WORD sectionCount = ntHeaders->FileHeader.NumberOfSections;

    // First section
    IMAGE_SECTION_HEADER* sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);

    // Flags for our magic sections
    bool foundStringTable = false;
    bool foundFuncDesc = false;
    bool foundVirtualFunc = false;
    bool foundVarDesc = false;
    bool foundVtableDesc = false;

    // Iterate through the sections
    for (WORD i = 0; i < sectionCount; i++, sectionHeader++) {
        const char* name = reinterpret_cast<const char*>(sectionHeader->Name);

        if (strcmp(name, StringTableSectionName) == 0) {
            foundStringTable = true;
            if (stringTableSection) 
                *stringTableSection = sectionHeader;
        }
        else if (strcmp(name, FunctionDescSectionName) == 0) {
            foundFuncDesc = true;
            if (functionDescSection) 
                *functionDescSection = sectionHeader;
        }
        else if (strcmp(name, VirtualFunctionDescSectionName) == 0) {
            foundVirtualFunc = true;
            if (virtualFunctionDescSection) 
                *virtualFunctionDescSection = sectionHeader;
        }
        else if (strcmp(name, VariableDescSectionName) == 0) {
            foundVarDesc = true;
            if (variableDescSection) 
                *variableDescSection = sectionHeader;
        }
        else if (strcmp(name, VtableDescSectionName) == 0) {
            foundVtableDesc = true;
            if (vtableDescSection) 
                *vtableDescSection = sectionHeader;
        }
    }

    // Return true only if all magic sections are found
    return foundStringTable &&
           foundFuncDesc &&
           foundVirtualFunc &&
           foundVarDesc &&
           foundVtableDesc;
}

void Amethyst::RuntimeImporter::UninitializedFunctionHandler()
{
    Log::Warning("[RuntimeImporter] Attempted to call an uninitialized function, don't expect happy endings...");
}

void Amethyst::RuntimeImporter::UninitializedDestructorHandler()
{
    Log::Warning("[RuntimeImporter] Attempted to call an uninitialized destructor, expect leaks...");
}