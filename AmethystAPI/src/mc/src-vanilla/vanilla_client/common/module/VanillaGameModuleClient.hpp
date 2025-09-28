/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src-client/common/module/GameModuleClient.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "gsl/gsl"

class Experiments;
class IResourcePackRepository;
class ResourcePackStack;
class BaseGameVersion;

/// @vptr { 0x4EBD550, this }
class VanillaGameModuleClient {
public:
    /// @vidx { 0, this }
    MC virtual ~VanillaGameModuleClient();

    virtual void unk_1();
    virtual void unk_2();
    virtual void unk_3();

    /// @vidx { 4, this }
    MC virtual void initializeResourceStack(const Experiments&, const gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>&, ResourcePackStack&, const BaseGameVersion&, GameModuleClient::ResourceLoadingPhase);
};