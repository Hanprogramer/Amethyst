#pragma once
#include <map>
#include <set>
#include "mc/src-deps/core/string/StringHash.hpp"
#include "mc/src/common/world/level/block/BlockLegacy.hpp"
#include "mc/src/common/SharedPtr.hpp"
#include "entt/container/dense_map.hpp"
#include "mc/src/common/world/level/block/Block.hpp"
#include <mc/src-deps/core/utility/StringUtils.hpp>

typedef std::map<HashedString, SharedPtr<BlockLegacy>> BlockLookupMap;
typedef entt::dense_map<HashType64, HashedString> BlockNameHashToHashedStringMap;

class BlockTypeRegistry {
public:
    struct BlockComplexAliasBlockState {
        HashedString stateName;
        int value;
    };

    struct LookupByNameImplReturnType {
    public:
        WeakPtr<BlockLegacy> blockLegacy;
        std::vector<BlockComplexAliasBlockState> states;
    };

    enum LookupByNameImplResolve : uint32_t {
        BlockLegacyResolve = 0,
        BlockResolve = 1
    };

    // Found in BlockTypeRegistry::registerBlock
    // 1.21.0.3 - 0x59DF328
    static std::set<std::string>* mKnownNamespaces() {
        static auto* knownNamespaces = reinterpret_cast<std::set<std::string>*>(SlideAddress(0x59DF328));
        return knownNamespaces;
    }

    // Found in BlockTypeRegistry::forEachBlock
    // 1.21.0.3 - 0x59DF300
    static BlockLookupMap* mBlockLookupMap() {
        static auto* lookupMap = reinterpret_cast<BlockLookupMap*>(SlideAddress(0x59DF300));
        return lookupMap;
    }

    // Found in BlockTypeRegistry::getBlockNameFromNameHash
    // 1.21.0.3 - 0x57D14E0
    static BlockNameHashToHashedStringMap* mBlockNameHashToStringMap() {
        static auto* map = reinterpret_cast<BlockNameHashToHashedStringMap*>(SlideAddress(0x57D14E0));
        return map;
    }

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9 0F 57 C0
    static const Block* getDefaultBlockState(const HashedString& name) {
        using function = Block*(*)(const HashedString&);
        static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9 0F 57 C0"));
        return func(name);
    }

    // Re-Implemented
    template<typename T, typename... Args>
    static WeakPtr<T> registerBlock(const std::string& blockName, Args&&... args) {
        HashedString hashedBlockName(blockName);
        Log::Info("hashed: {}", hashedBlockName.getHash());

        // Ensure the block has a name
        if (blockName.empty()) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a name!");
        }

        SharedPtr<T> block = SharedPtr<T>::make(blockName, std::forward<Args>(args)...);

        // Convert the string to lowercase and validate its namespace
        std::string lowercaseName = Util::toLower(blockName);
        size_t separator = lowercaseName.find(':');

        if (separator == std::string::npos) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a namespace!");
        }

        if (separator == 0) {
            throw std::exception("BlockTypeRegistry: attempting to register a block with an empty namespace!");
        }

        // Add the namespace to a set of known namespaces
        std::string blockNamespace = lowercaseName.substr(0, separator);
        std::set<std::string>* namespaceSet = BlockTypeRegistry::mKnownNamespaces();
        namespaceSet->insert(blockNamespace);

        // Add the block to the lookup map
        BlockLookupMap* blockLookupMap = BlockTypeRegistry::mBlockLookupMap();
        blockLookupMap->emplace(std::make_pair(hashedBlockName, block));

        // Add the hashed name to a lookup map
        BlockNameHashToHashedStringMap* hashedNameMap = BlockTypeRegistry::mBlockNameHashToStringMap();
        hashedNameMap->emplace(std::make_pair(hashedBlockName.getHash(), hashedBlockName));

        return block;
    }

    // 1.21.0.3 - 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E0 44 89 44 24
    static LookupByNameImplReturnType _lookupByNameImpl(const HashedString& name, int data, LookupByNameImplResolve resolve) {
        using function = decltype(&BlockTypeRegistry::_lookupByNameImpl);
        static auto func = std::bit_cast<function>(SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E0 44 89 44 24"));
        return func(name, data, resolve);
    }
};
