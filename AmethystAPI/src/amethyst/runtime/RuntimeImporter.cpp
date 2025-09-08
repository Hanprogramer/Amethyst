#include <amethyst/runtime/RuntimeImporter.hpp>
#include <amethyst/Log.hpp>
#include <amethyst/Memory.hpp>
#include <minecraft/src/common/resources/ResourcePackRepository.hpp>

std::unordered_map<void*, std::unordered_map<std::string, uintptr_t*>> Amethyst::RuntimeImporter::ImportAddresses{};
std::unordered_map<void*, std::unordered_map<uint32_t, std::string>>  Amethyst::RuntimeImporter::IndexToImportName{};
std::unordered_map<void*, std::unordered_map<uint32_t, std::string>>  Amethyst::RuntimeImporter::IndexToImportSignature{};

bool Amethyst::RuntimeImporter::LoadImports(void* handle)
{
    if (ImportAddresses.count(handle) != 0) {
        Log::Warning("[RuntimeImporter] Imports for this module have already been loaded, skipping.");
        return true;
    }

    uintptr_t base = reinterpret_cast<uintptr_t>(handle);
    // Get the DOS header
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return false;
    }

    // Get the NT headers
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return false;
    }

    // Iterate through the sections to find our custom sections
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeaders);
    uint16_t numberOfSections = ntHeaders->FileHeader.NumberOfSections;

    // Lots of sections to find...
    IMAGE_SECTION_HEADER* rivdtSection = nullptr;
    IMAGE_SECTION_HEADER* rifdtSection = nullptr;
    IMAGE_SECTION_HEADER* rimtSection = nullptr;
    IMAGE_SECTION_HEADER* ristSection = nullptr;
    IMAGE_SECTION_HEADER* idnewSection = nullptr;
    for (int i = 0; i < numberOfSections; i++) {
        std::string sectionName(reinterpret_cast<char*>(section[i].Name), strnlen_s(reinterpret_cast<char*>(section[i].Name), IMAGE_SIZEOF_SHORT_NAME));
        if (sectionName == RUNTIME_IMPORT_FUNC_DESC_TABLE) {
            rifdtSection = &section[i];
        }
        else if (sectionName == RUNTIME_IMPORT_MANGLE_TABLE) {
            rimtSection = &section[i];
        }
        else if (sectionName == RUNTIME_IMPORT_SIG_TABLE) {
            ristSection = &section[i];
        }
        else if (sectionName == NEW_IMPORT_DIRECTORY) {
            idnewSection = &section[i];
        }
        else if (sectionName == RUNTIME_IMPORT_VAR_DESC_TABLE) {
            rivdtSection = &section[i];
        }
    }

    // Ensure we found all required sections
    if (!rimtSection || !ristSection || !rifdtSection || !idnewSection || !rivdtSection) {
        Log::Warning("[RuntimeImporter] One or more required sections not found in module.");
        return false;
    }

    ImportAddresses[handle] = {};
    IndexToImportName[handle] = {};
    IndexToImportSignature[handle] = {};

    // First we go through the RIMT and RIST sections to build a mapping of index -> (name, signature)
    StringTable& rimtStringTable = *reinterpret_cast<StringTable*>(base + rimtSection->VirtualAddress);
    uint32_t nameOffset = 0;
    for (auto i = 0; i < rimtStringTable.stringCount; i++) {
        std::string name = reinterpret_cast<const char*>(reinterpret_cast<uintptr_t>(&rimtStringTable.strings) + nameOffset);
        IndexToImportName[handle][i] = name;
        nameOffset += static_cast<uint32_t>(name.length()) + 1; // +1 for null terminator
    }

    StringTable& ristStringTable = *reinterpret_cast<StringTable*>(base + ristSection->VirtualAddress);
    uint32_t sigOffset = 0;
    for (auto i = 0; i < rimtStringTable.stringCount; i++) {
        std::string signature = reinterpret_cast<const char*>(reinterpret_cast<uintptr_t>(&ristStringTable.strings) + +sigOffset);
        IndexToImportSignature[handle][i] = signature;
        sigOffset += static_cast<uint32_t>(signature.length()) + 1; // +1 for null terminator
    }

    // Now we can go through the RIFDT and RIVDT section to actually perform the imports
    FunctionDescriptorTable& rifdtTable = *reinterpret_cast<FunctionDescriptorTable*>(base + rifdtSection->VirtualAddress);
    VariableDescriptorTable& rivdtTable = *reinterpret_cast<VariableDescriptorTable*>(base + rivdtSection->VirtualAddress);

    // Unprotect "Minecraft.Windows.exe" IAT so we can write to it
    DWORD oldProtection;
    UnprotectMemory(base + rifdtTable.iatRva, rifdtTable.iatSize * sizeof(uintptr_t), &oldProtection);

    // Iterate through each function descriptor and perform the import
    for (auto i = 0; i < rifdtTable.functionCount; i++) {
        FunctionDescriptor& funcDesc = (&rifdtTable.functions)[i];
        std::string importName = IndexToImportName[handle][funcDesc.nameIndex];
        uint32_t iatIndex = funcDesc.iatIndex;
        uintptr_t& iatEntry = *(&reinterpret_cast<uintptr_t*>(base + rifdtTable.iatRva)[iatIndex]);
        ImportAddresses[handle][importName] = &iatEntry;
        if (!funcDesc.isSignature) {
            if (funcDesc.address == 0x0)
            {
                Log::Warning("[RuntimeImporter] Import '{}' has a nullptr address, setting to fallback! (Don't expect it to work flawlessly)", importName);
                iatEntry = reinterpret_cast<uintptr_t>(&UnloadedImportFallback);
            }
            else {
                iatEntry = SlideAddress(funcDesc.address);
            }
        }
        else {
            if (IndexToImportSignature[handle].count(static_cast<uint32_t>(funcDesc.signatureIndex)) == 0) {
                Log::Warning("[RuntimeImporter] No signature found for import '{}', setting to fallback! (Don't expect it to work flawlessly)", importName);
                iatEntry = reinterpret_cast<uintptr_t>(&UnloadedImportFallback);
            }
            else {
                std::string& signature = IndexToImportSignature[handle][static_cast<uint32_t>(funcDesc.signatureIndex)];
                auto scan = SigScanSafe(signature);
                if (!scan.has_value()) {
                    Log::Warning("[RuntimeImporter] SigScan failed for import '{}', signature = '{}', setting to fallback! (Don't expect it to work flawlessly)", importName, signature);
                    iatEntry = reinterpret_cast<uintptr_t>(&UnloadedImportFallback);
                }
                else {
                    iatEntry = scan.value();
                }
            }
        }
    }

    // Iterate through each variable descriptor and perform the import
    for (auto i = 0; i < rivdtTable.variableCount; i++) {
        VariableDescriptor& varDesc = (&rivdtTable.variables)[i];
        std::string importName = IndexToImportName[handle][varDesc.nameIndex];
        uint32_t iatIndex = varDesc.iatIndex;
        uintptr_t& iatEntry = *(&reinterpret_cast<uintptr_t*>(base + rivdtTable.iatRva)[iatIndex]);
        ImportAddresses[handle][importName] = &iatEntry;
        iatEntry = SlideAddress(varDesc.address);
    }

    Log::Info("[RuntimeImporter] Loaded {} imports!", rifdtTable.functionCount);
    return true;
}

bool Amethyst::RuntimeImporter::UnloadImports(void* handle)
{
    if (ImportAddresses.find(handle) == ImportAddresses.end()) {
        Log::Warning("[RuntimeImporter] No imports loaded for this module, cannot unload.");
        return false;
    }

    for (auto& [name, addressPtr] : ImportAddresses[handle]) {
        *addressPtr = reinterpret_cast<uintptr_t>(&UnloadedImportFallback);
    }

    ImportAddresses.erase(handle);
    IndexToImportName.erase(handle);
    IndexToImportSignature.erase(handle);
    return true;
}

uintptr_t Amethyst::RuntimeImporter::GetAddress(void* handle, const std::string& name)
{
    uintptr_t* address = GetMutableAddress(handle, name);
    if (!address) {
        return 0;
    }
    return *address;
}

uintptr_t* Amethyst::RuntimeImporter::GetMutableAddress(void* handle, const std::string& name)
{
    char buffer[MAX_PATH];
    GetModuleFileNameA((HMODULE)handle, buffer, MAX_PATH);
    std::string moduleName;
    if (buffer != nullptr) {
        moduleName = std::string(buffer);
    } else {
        moduleName = "Unknown Module";
    }

    if (ImportAddresses.count(handle) == 0) {
        Log::Warning("[RuntimeImporter] Couldn't find imports for '{}'.", moduleName);
        return nullptr;
    }
    
    if (ImportAddresses[handle].count(name) == 0) {
        Log::Warning("[RuntimeImporter] Couldn't find import '{}' for '{}'.", name, moduleName);
        return nullptr;
    }

    return ImportAddresses[handle][name];
}

bool Amethyst::RuntimeImporter::HasRuntimeImports(void* handle)
{
    uintptr_t base = reinterpret_cast<uintptr_t>(handle);
    // Get the DOS header
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return false;
    }

    // Get the NT headers
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return false;
    }

    // Iterate through the sections to find our custom sections
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeaders);
    uint16_t numberOfSections = ntHeaders->FileHeader.NumberOfSections;

    // Lots of sections to find...
    IMAGE_SECTION_HEADER* rifdtSection = nullptr;
    IMAGE_SECTION_HEADER* rimtSection = nullptr;
    IMAGE_SECTION_HEADER* ristSection = nullptr;
    IMAGE_SECTION_HEADER* idnewSection = nullptr;
    for (int i = 0; i < numberOfSections; i++) {
        std::string sectionName(reinterpret_cast<char*>(section[i].Name), strnlen_s(reinterpret_cast<char*>(section[i].Name), IMAGE_SIZEOF_SHORT_NAME));
        if (sectionName == RUNTIME_IMPORT_FUNC_DESC_TABLE) {
            rifdtSection = &section[i];
        } else if (sectionName == RUNTIME_IMPORT_MANGLE_TABLE) {
            rimtSection = &section[i];
        } else if (sectionName == RUNTIME_IMPORT_SIG_TABLE) {
            ristSection = &section[i];
        } else if (sectionName == NEW_IMPORT_DIRECTORY) {
            idnewSection = &section[i];
        }
    }

    return rifdtSection != nullptr && rimtSection != nullptr && ristSection != nullptr && idnewSection != nullptr;
}

void Amethyst::RuntimeImporter::UnloadedImportFallback()
{
    Log::Warning("[RuntimeImporter] Attempted to use an import that was not been loaded succesfully, expect crashes!");
}
