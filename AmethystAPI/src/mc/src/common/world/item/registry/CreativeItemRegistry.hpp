/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>

class CreativeItemGroupCategory;
class CreativeGroupInfo;
class CreativeItemEntry;
class ItemInstance;
class ItemRegistryRef;
class BaseGameVersion;

class CreativeItemRegistry : public Bedrock::EnableNonOwnerReferences {
public:
    std::vector<CreativeItemEntry> mCreativeItems;
    std::vector<CreativeGroupInfo> mCreativeGroups;
    std::unordered_map<CreativeItemCategory, CreativeItemGroupCategory> mCreativeGroupCategories;
    std::byte mCreativeNetIdIndex[64]; // std::unordered_map<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0>,unsigned __int64,std::hash<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> >,std::equal_to<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> >,std::allocator<std::pair<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> const ,unsigned __int64> > > mCreativeNetIdIndex;

public:
	/// @vidx {0}
	MC virtual ~CreativeItemRegistry() override;

//begin members:
	MC CreativeItemGroupCategory* getCreativeCategory(CreativeItemCategory category);

	MC UnknownReturn getCreativeGroup(unsigned int groupIndex);

	MC const std::vector<CreativeItemEntry>& getCreativeItemEntries();

	MC CreativeItemEntry* getItemEntry(unsigned int entryIndex);

	MC UnknownReturn clear();

	CreativeItemEntry* findCreativeItemEntry(const ItemInstance& itemInstance);

	MC UnknownReturn forEachCreativeItemInstance(std::function<bool(const ItemInstance&)> callback) const;

	MC UnknownReturn logRegistry(const std::string& logPrefix);

	/// @signature {40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B D2}
	MC CreativeItemGroupCategory* newCreativeCategory(const std::string& categoryName, CreativeItemCategory category);

	MC CreativeGroupInfo* newCreativeGroup(CreativeItemCategory category, const HashedString& groupName, const ItemInstance& iconItem);

	MC UnknownReturn newItemEntry(const ItemInstance& itemInstance);

	MC void resetGroups();

	MC UnknownReturn takeCreativeList(std::vector<CreativeItemEntry>&& newEntries);

	MC CreativeItemEntry* updateItemEntry(unsigned int entryIndex, const ItemInstance& newItemInstance);

	MC void updateNetIdMap();
};

static_assert(offsetof(CreativeItemRegistry, mCreativeItems) == 24);