#include "amethyst/runtime/importing/data/pe32+/V1/PEFunctionSymbol.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalFunctionSymbol.hpp"

namespace Amethyst::Importing::PE::V1 {
	std::string PEFunctionSymbol::GetKind() const {
		return "function";
	}

	bool PEFunctionSymbol::IsShadowSymbol() const {
		return false;
	}

	uint32_t PEFunctionSymbol::GetFormatVersion() const {
		return 1;
	}

	std::unique_ptr<CanonicalSymbol> PEFunctionSymbol::Canonize() const {
		auto canon = std::make_unique<PECanonicalFunctionSymbol>();
		canon->TargetOffset = TargetOffset;
		canon->Name = Name;
		canon->IsShadow = IsShadowSymbol();
		canon->IsVirtual = IsVirtual;
		canon->VirtualIndex = VirtualIndex;
		canon->VirtualTable = VirtualTable;
		canon->IsSignature = IsSignature;
		canon->Signature = Signature;
		canon->Address = Address;
		return canon;
	}

	void PEFunctionSymbol::ReadFrom(SimpleBinaryReader& reader) {
		AbstractPEImportedSymbol::ReadFrom(reader);
		IsVirtual = reader.Read<uint8_t>() != 0;
		if (IsVirtual) {
			VirtualIndex = reader.Read<uint32_t>();
			VirtualTable = reader.ReadPrefixedString();
		}
		else {
			IsSignature = reader.Read<uint8_t>() != 0;
			if (IsSignature) {
				Signature = reader.ReadPrefixedString();
			}
			else {
				Address = reader.Read<uint64_t>();
			}
		}
	}

	std::string PEFunctionSymbol::ToString() const {
		std::stringstream fields;
		if (IsVirtual) {
			fields << std::format("Virtual[{}, {}]", VirtualIndex, VirtualTable);
		}
		else if (IsSignature) {
			fields << std::format("Signature[{}]", Signature);
		}
		else {
			fields << std::format("Address[{:x}]", Address);
		}
		return std::format("{} -> PEFunctionSymbol[{}]", AbstractPEImportedSymbol::ToString(), fields.str());
	}
}