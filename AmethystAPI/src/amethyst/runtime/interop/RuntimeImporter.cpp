#include <amethyst/runtime/interop/RuntimeImporter.hpp>
#include <amethyst/Log.hpp>
#include <amethyst/Memory.hpp>
#include "mc/src-client/common/client/world/WorldCreationHelper.hpp"
#include "amethyst/runtime/importing/data/HeaderFactory.hpp"
#include "amethyst/runtime/importing/data/AbstractHeader.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalHeader.hpp"
#include <span>
#include <spanstream>
using namespace Amethyst::Importing;

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

// YES this looks insane. It's literally a tiny trampoline to disable MSVC's deleting thunk
// because the generated thunk that calls this already deletes, and double-free = sad. Keep it. Do not touch.
static constexpr const uint8_t VirtualDestructorDeletingDisableBlock[] = {
    0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // mov rax, 0x1000000000000000
    0x31, 0xD2,                                                 // xor edx, edx (sets delete flag to false)
    0xFF, 0xE0                                                  // jmp rax
};

std::unordered_map<HMODULE, Amethyst::RuntimeImporter*> Amethyst::RuntimeImporter::sImporters = {};

Amethyst::RuntimeImporter::RuntimeImporter(HMODULE moduleHandle) : 
	mModule(moduleHandle),
    mInitialized(false)
{
    sImporters.insert({moduleHandle, this});
}

Amethyst::RuntimeImporter::~RuntimeImporter()
{
    sImporters.erase(mModule);
}

bool Amethyst::RuntimeImporter::IsDestructor(const std::string& name)
{
    return name.starts_with("??1") || name.starts_with("?_G") || name.starts_with("?_E");
}

bool Amethyst::RuntimeImporter::HasImporter(HMODULE moduleHandle)
{
    return sImporters.find(moduleHandle) != sImporters.end();
}

std::shared_ptr<Amethyst::RuntimeImporter> Amethyst::RuntimeImporter::GetImporter(HMODULE moduleHandle)
{
    if (HasImporter(moduleHandle)) {
        return sImporters.find(moduleHandle)->second->shared_from_this();
    }
    return std::shared_ptr<Amethyst::RuntimeImporter>(new Amethyst::RuntimeImporter(moduleHandle));
}

bool Amethyst::RuntimeImporter::ResolveAll() const
{
    uintptr_t base = reinterpret_cast<uintptr_t>(mModule);

    // Grab the ancient DOS header
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        Log::Error("DOS header signature is NOT 'MZ'...");
        Log::Error("What the fuck did you do to make this happen?");
        return false;
    }

    // Jump to NT headers
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    WORD sectionCount = ntHeaders->FileHeader.NumberOfSections;

    // First section
    IMAGE_SECTION_HEADER* sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);

    // Iterate through the sections
    for (WORD i = 0; i < sectionCount; i++, sectionHeader++) {
        const char* name = reinterpret_cast<const char*>(sectionHeader->Name);
        if (strcmp(name, ".rtih") == 0) {
            std::span<char> span(reinterpret_cast<char*>(base + sectionHeader->VirtualAddress), sectionHeader->SizeOfRawData);
            std::spanstream stream(span);
			SimpleBinaryReader reader(stream);
            auto header = HeaderFactory::Create(AbstractHeader::PeekInfo(reader));
			header->ReadFrom(reader);
            auto canon = header->Canonize();
            auto transformed = canon->Transform<PE::PECanonicalHeader>();
            for (const auto& symbol : transformed->Symbols) {
				symbol->Resolve({ mModule, transformed });
            }
			break;
        }
    }
}

// This is our safety net for “lol did you forget to init this function?”
// It’s ugly, it’s a runtime trap, but better than crashing immediately.
void Amethyst::RuntimeImporter::UninitializedFunctionHandler()
{
    Log::Warning("Attempted to call an uninitialized function, don't expect happy endings...");
}

void Amethyst::RuntimeImporter::UninitializedDestructorHandler()
{
    Log::Warning("Attempted to call an uninitialized destructor, expect leaks...");
}