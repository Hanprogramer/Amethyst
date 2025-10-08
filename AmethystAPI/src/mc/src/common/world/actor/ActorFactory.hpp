///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/actor/ActorType.hpp>

class ActorGoalFactory;
class ActorDefinitionGroup;
class ActorDefinitionIdentifier;
class Experiments;
class CompoundTag;
class LevelChunk;
class BlockSource;
class DataLoadHelper;
class DimensionHeightRange;
class ActorFactoryData;
class IEntityInitializer;
class Level;
class ActorInfo;
class Actor;

struct OwnerStorageEntity {
    std::optional<EntityContext> mContext;
};

class ActorFactory {
public:
	/// @vidx {0}
	MC virtual ~ActorFactory();

//begin members:
	ActorFactory(gsl::not_null<Bedrock::NonOwnerPointer<Level>>);

	ActorGoalFactory& getGoalFactory();

	void setDefinitionGroup(ActorDefinitionGroup* unk0);

	void setEntityInitializer(std::shared_ptr<IEntityInitializer> unk0);

	bool hasActor(const ActorDefinitionIdentifier& unk0, ActorType unk1) const;

	std::vector<std::pair<std::string, const ActorDefinitionIdentifier*>> buildSummonEntityTypeEnum(const Experiments& unk0) const;

	UnknownReturn buildUniqueSummonableActorList(const Experiments& unk0) const;

	void _buildSummonableActorList(const Experiments& unk0, std::function<void(const std::string&, const ActorFactoryData&)> unk1) const;

	OwnerPtr<EntityContext> _constructActor(const ActorDefinitionIdentifier& unk0, const Vec3& unk1, const Vec2& unk2, const std::vector<std::string>* unk3) const;

	void _loadDefinitionGroups(ActorDefinitionGroup* unk0);

	void _loadDefinitionsHelper();

	bool _validateActorData(CompoundTag& unk0, ActorDefinitionIdentifier& unk1, Vec3& unk2, const LevelChunk* unk3) const;

	void applyEntityInitializer(std::unique_ptr<Actor> unk0, EntityContext& unk1) const;

	void clearDefinitionGroup();

	static void clearEntityMappings();

	OwnerPtr<EntityContext> clientCreateDisplayActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2, const Vec2& unk3);

	OwnerPtr<EntityContext> createActor(const std::string& unk0, const ActorDefinitionIdentifier& unk1, Actor* unk2, const Vec3& unk3, const Vec2& unk4);

	OwnerPtr<EntityContext> createBornActor(const ActorDefinitionIdentifier& unk0, Actor* unk1);

	OwnerPtr<EntityContext> createBornActor(const ActorDefinitionIdentifier& unk0, const BlockPos& unk1);

	/// @signature {40 53 55 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4D 8B E1 49 8B E8 48 8B DA}
	MC OwnerPtr<EntityContext> createSpawnedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2, const Vec2& unk3);

	OwnerPtr<EntityContext> createSummonedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1, const Vec3& unk2);

	OwnerPtr<EntityContext> createTransformedActor(const ActorDefinitionIdentifier& unk0, Actor* unk1);

	UnknownReturn digestIdentifierListFromServer(const std::vector<ActorInfo>& unk0);

	static void fillFactoryData(const ActorDefinitionIdentifier& unk0, const ActorDefinitionIdentifier& unk1, const std::unordered_map<std::string, ActorFactoryData, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, ActorFactoryData>>>& unk2, ActorFactoryData& unk3);

	static Actor* fixLegacyEntity(BlockSource& unk0, const CompoundTag* unk1);

	UnknownReturn generateActorIdentifierList() const;

	void init(const Experiments& unk0);

	OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1, const DimensionHeightRange& unk2, const LevelChunk* unk3);

	OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1, const DimensionHeightRange& unk2);

	OwnerPtr<EntityContext> loadActor(CompoundTag* unk0, DataLoadHelper& unk1);

	ActorType lookupEntityType(const ActorDefinitionIdentifier& unk0) const;
};