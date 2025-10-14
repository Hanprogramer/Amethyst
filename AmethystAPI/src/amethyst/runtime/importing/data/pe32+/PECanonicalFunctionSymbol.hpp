#pragma once
#include "amethyst/runtime/importing/data/CanonicalSymbol.hpp"

namespace Amethyst::Importing::PE {
	class PECanonicalFunctionSymbol :
		public CanonicalSymbol
	{
	public:
		bool IsVirtual = false;
		uint32_t VirtualIndex = 0;
		std::string VirtualTable = "";
		bool IsSignature = false;
		std::string Signature = "";
		uint64_t Address = 0x0;

		virtual std::string GetFormatType() const override;
		virtual std::string GetKind() const override;
		virtual std::string ToString() const override;
	};
}