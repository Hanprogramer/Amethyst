#pragma once
#include "amethyst/runtime/importing/data/CanonicalSymbol.hpp"

namespace Amethyst::Importing::PE {
	class PECanonicalDataSymbol :
		public CanonicalSymbol
	{
	public:
		bool IsVirtualTable = false;
		uint64_t Address = 0x0;

		virtual std::string GetFormatType() const override;
		virtual std::string GetKind() const override;
		virtual std::string ToString() const override;
	};
}