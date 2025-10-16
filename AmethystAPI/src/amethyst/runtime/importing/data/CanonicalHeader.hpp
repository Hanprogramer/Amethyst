#pragma once
#include <memory>

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
			static_assert(!std::is_same_v<T, T>, "Transforming CanonicalHeader to T not implemented.");
		}

		template<>
		PE::PECanonicalHeader* Transform<PE::PECanonicalHeader>();
	};
}