#pragma once

namespace Amethyst::Importing {
	namespace PE {
		class PECanonicalHeader;
	}

	class CanonicalSymbol;
	class CanonicalHeader {
	public:
		std::vector<std::unique_ptr<CanonicalSymbol>> Symbols;

		virtual ~CanonicalHeader() = default;
		virtual std::string GetFormatType() const = 0;
		virtual std::string ToString() const;

		template<typename T = CanonicalHeader>
		T* Transform() {
			static_assert(false, "Transforming CanonicalHeader to T not implemented.");
		}

		template<>
		PE::PECanonicalHeader* Transform<PE::PECanonicalHeader>();
	};
}