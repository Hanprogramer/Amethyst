#pragma once
#include <map>
#include <amethyst/Log.hpp>
#include <amethyst/Memory.hpp>
#include <amethyst/Config.hpp>
#include "minecraft/src-deps/core/string/StringHash.hpp"

namespace Amethyst {
	class SymbolLoader {
	public:
        void Start(const Config& config);

		void* ResolveSymbol(std::string& symbol) {
             Log::Warning("[SymbolLoader.hpp] No address was associated with symbol '{}'", symbol);
             return nullptr;
		}

	private:
         std::map<HashType64, uintptr_t> mSymbolHashToAddress;

         void LoadDefinitions(const std::string& definitionsFile);
	};
};