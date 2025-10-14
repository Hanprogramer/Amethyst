#include "amethyst/runtime/importing/data/pe32+/PECanonicalFunctionSymbol.hpp"

namespace Amethyst::Importing::PE {
	std::string PECanonicalFunctionSymbol::GetFormatType() const {
		return "pe32+";
	}

	std::string PECanonicalFunctionSymbol::GetKind() const {
		return "function";
	}

	std::string PECanonicalFunctionSymbol::ToString() const {
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
		return std::format("{} -> PECanonicalFunctionSymbol[{}]", CanonicalSymbol::ToString(), fields.str());
	}
}