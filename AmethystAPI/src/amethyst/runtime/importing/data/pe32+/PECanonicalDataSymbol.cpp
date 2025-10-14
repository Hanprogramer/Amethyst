#include "amethyst/runtime/importing/data/pe32+/PECanonicalDataSymbol.hpp"

namespace Amethyst::Importing::PE {
	std::string PECanonicalDataSymbol::GetFormatType() const {
		return "pe32+";
	}

	std::string PECanonicalDataSymbol::GetKind() const {
		return "data";
	}

	std::string PECanonicalDataSymbol::ToString() const {
		std::stringstream fields;
		if (IsVirtualTable) {
			fields << "VirtualTable, ";
		}
		fields << std::format("Address[{:x}]", Address);
		return std::format("{} -> PECanonicalDataSymbol[{}]", CanonicalSymbol::ToString(), fields.str());
	}
}