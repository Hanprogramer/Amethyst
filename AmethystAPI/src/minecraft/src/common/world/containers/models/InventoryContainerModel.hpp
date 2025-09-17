/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "minecraft/src/common/world/containers/models/ContainerModel.hpp"

enum class ContainerEnumName;
class Player;

/// @vptr {0x4DE9A00}
class InventoryContainerModel : 
    public ContainerModel 
{
public:
    Player& mPlayer;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F9 41 8B F0}
    MC InventoryContainerModel(ContainerEnumName, int, Player&);
    
    /// @vidx {inherit}
    virtual void containerContentChanged(int) override;
    /// @vidx {inherit}
    virtual ~InventoryContainerModel() override;
    /// @vidx {inherit}
    virtual void postInit() override;
    /// @vidx {inherit}
    virtual void releaseResources() override;
    /// @vidx {inherit}
    virtual ContainerWeakRef getContainerWeakRef() override;
    /// @vidx {inherit}
    virtual bool isValid() override;
    /// @vidx {inherit}
    virtual Container* _getContainer() override;
    /// @vidx {inherit}
    virtual int _getContainerOffset() override;
};

