#pragma once

namespace Amethyst::Importing {
	namespace PE {
		class PECanonicalDataSymbol;
		class PECanonicalFunctionSymbol;
	}

	class CanonicalSymbol {
	public:
		std::string Name = "";
		bool IsShadow = false;

		virtual ~CanonicalSymbol() = default;
		virtual std::string GetFormatType() const = 0;
		virtual std::string GetKind() const = 0;
		virtual std::string ToString() const;

		template<typename T = CanonicalSymbol>
		T* Transform() {
			static_assert(false, "Transforming CanonicalSymbol to T not implemented.");
		}

		template<>
		PE::PECanonicalDataSymbol* Transform<PE::PECanonicalDataSymbol>();
		template<>
		PE::PECanonicalFunctionSymbol* Transform<PE::PECanonicalFunctionSymbol>();
	};
}