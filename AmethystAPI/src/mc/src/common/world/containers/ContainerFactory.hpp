#pragma once
#include <memory>
#include "mc/src/common/world/containers/managers/models/ContainerManagerModel.hpp"

class Player;
class IContainerManager;
class ContainerFactory {
public:
    static void _setPlayerContainerManagerModel(Player& player, std::shared_ptr<IContainerManager> manager);
    static std::weak_ptr<IContainerManager> _getPlayerContainerManagerModel(const Player& player);

    template <typename T, typename... Args>
    requires std::is_base_of_v<IContainerManager, T>
    static std::weak_ptr<T> clientCreateContainerManagerModel(Player& player, Args&&... args) {
        auto model = std::make_shared<T>(std::forward<Args>(args)...);
        model->postInit();
        _setPlayerContainerManagerModel(player, model);
        return model;
    }
};