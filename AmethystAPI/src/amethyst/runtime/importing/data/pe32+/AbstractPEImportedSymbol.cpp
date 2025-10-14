#include "amethyst/runtime/importing/data/pe32+/AbstractPEImportedSymbol.hpp"

namespace Amethyst::Importing::PE {
	std::string AbstractPEImportedSymbol::GetFormatType() const {
		return "pe32+";
	}

	void AbstractPEImportedSymbol::ReadFrom(SimpleBinaryReader& reader) {
		AbstractSymbol::ReadFrom(reader);
		TargetOffset = reader.Read<uint32_t>();
	}

	std::string AbstractPEImportedSymbol::ToString() const {
		return std::format("{} -> AbstractPEImportedSymbol[TargetOffset: {:x}]", AbstractSymbol::ToString(), TargetOffset);
	}
}
