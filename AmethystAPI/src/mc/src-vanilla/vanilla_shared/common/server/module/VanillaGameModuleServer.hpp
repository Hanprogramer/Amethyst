/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

/// @vptr { 0x4EC7070, this }
class VanillaGameModuleServer {
public:
    /// @vidx { 0, this }
    MC virtual ~VanillaGameModuleServer();

    virtual void unk_1();

    /// @vidx { 2, this }
    MC virtual void initializeBehaviorStack(const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};