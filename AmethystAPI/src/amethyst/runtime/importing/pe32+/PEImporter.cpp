#include "amethyst/runtime/importing/pe32+/PEImporter.hpp"
#include <span>
#include <spanstream>

#include "amethyst/runtime/importing/data/pe32+/PECanonicalHeader.hpp"
#include "amethyst/runtime/utility/SimpleBinaryReader.hpp"
#include "amethyst/runtime/importing/data/AbstractHeader.hpp"
#include "amethyst/runtime/importing/data/HeaderFactory.hpp"

namespace Amethyst::Importing::PE {
	PEImporter::PEImporter(void* module) :
		Importer(module)
	{
		Assert(!IsResolved(), "Symbols are already resolved for this module");
		Assert(mModule != nullptr, "PEImporter module handle cannot be null");
		auto [rtih, rtis] = GetSections(mModule);
		mRTIHSection = rtih;
		mRTISSection = rtis;
		mState = reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(mModule) + mRTISSection->VirtualAddress);
		mHeader = LoadHeader(mModule, mRTIHSection, mRTISSection);
	}

	PEImporter::~PEImporter() {
		if (mState && (*mState & 0xFFull) == 1)
			*mState = (*mState & ~0xFFull) | 0;
	}

	void PEImporter::ResolveAll() {
		Assert(mHeader != nullptr, "Cannot resolve symbols without a valid header");
		Assert(!IsResolved(), "Symbols are already resolved for this module");
		for (auto& symbol : mHeader->Symbols) {
			ResolutionContext ctx = {
				.ModuleHandle = mModule,
				.Header = mHeader.get()
			};
			symbol->Resolve(ctx);
		}
		if (mState)
			*mState = (*mState & ~0xFFull) | 1;
	}

	bool PEImporter::IsResolved() const {
		return mHeader != nullptr && mState != nullptr && (*mState & 0xFFull) == 1;
	}

	std::tuple<IMAGE_SECTION_HEADER*, IMAGE_SECTION_HEADER*> PEImporter::GetSections(void* module) {
		uintptr_t base = reinterpret_cast<uintptr_t>(module);
		IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			Assert(false, "DOS header signature was NOT 'MZ'...");
			return { nullptr, nullptr };
		}

		IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
		WORD sectionCount = ntHeaders->FileHeader.NumberOfSections;
		IMAGE_SECTION_HEADER* sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);
		IMAGE_SECTION_HEADER* rtih = nullptr;
		IMAGE_SECTION_HEADER* rtis = nullptr;

		for (WORD i = 0; i < sectionCount; i++, sectionHeader++) {
			const char* name = reinterpret_cast<const char*>(sectionHeader->Name);
			if (strcmp(name, ".rtih") == 0) {
				rtih = sectionHeader;
			}
			else if (strcmp(name, ".rtis") == 0) {
				rtis = sectionHeader;
			}

			if (rtih != nullptr && rtis != nullptr) {
				break;
			}
		}
		return { rtih, rtis };
	}

	std::unique_ptr<CanonicalHeader> PEImporter::LoadHeader(void* module, IMAGE_SECTION_HEADER* rtih, IMAGE_SECTION_HEADER* rtis) {
		if (rtih == nullptr || rtis == nullptr) {
			Assert(false, "RTIH and RTIS section headers cannot be null");
			return nullptr;
		}

		Assert(rtih != nullptr, "RTIH section header cannot be null");
		Assert(rtis != nullptr, "RTIS section header cannot be null");
		
		uintptr_t base = reinterpret_cast<uintptr_t>(module);
		std::span<char> data = {
			reinterpret_cast<char*>(base + rtih->VirtualAddress),
			rtih->SizeOfRawData
		};

		std::spanstream ss(data);
		SimpleBinaryReader reader(ss);
		auto type = AbstractHeader::PeekInfo(reader);
		auto header = HeaderFactory::Create(type);
		if (header == nullptr) {
			Assert(false, "Failed to create header of type '{}'", type.ToString());
			return nullptr;
		}

		header->ReadFrom(reader);
		return header->Canonize();
	}

	std::unique_ptr<PEImporter> PEImporter::Create(void* module) {
		Assert(module != nullptr, "PEImporter module handle cannot be null");
		auto [rtih, rtis] = GetSections(module);
		if (rtih == nullptr || rtis == nullptr) {
			Log::Warning("Module 0x{:x} doesn't import from 'Minecraft.Windows', skipping resolution.", reinterpret_cast<uintptr_t>(module));
			return nullptr;
		}

		Assert((ReadState(module) & 0xFFull) != 1, "Symbols are already resolved for this module");
		return std::make_unique<PEImporter>(module);
	}

	uint64_t PEImporter::ReadState(void* module) {
		auto [rtih, rtis] = GetSections(module);
		Assert(rtih != nullptr, "Failed to find .rtih section in module");
		Assert(rtis != nullptr, "Failed to find .rtis section in module");

		uintptr_t base = reinterpret_cast<uintptr_t>(module);
		uint64_t* state = reinterpret_cast<uint64_t*>(base + rtis->VirtualAddress);
		return *state;
	}

	void PEImporter::WriteState(void* module, uint64_t state) {
		auto [rtih, rtis] = GetSections(module);
		Assert(rtih != nullptr, "Failed to find .rtih section in module");
		Assert(rtis != nullptr, "Failed to find .rtis section in module");
		uintptr_t base = reinterpret_cast<uintptr_t>(module);
		uint64_t* currentState = reinterpret_cast<uint64_t*>(base + rtis->VirtualAddress);
		*currentState = state;
	}
}