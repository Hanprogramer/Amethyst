#pragma once
#include <memory>
#include "minecraft/src-client/common/client/game/IClientInstance.hpp"
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include "minecraft/src-client/common/client/gui/screens/models/MinecraftScreenModel.hpp"

class IAdvancedGraphicsOptions;

class SceneCreationUtils {
public:
    template <typename T, typename... Args>
    static std::shared_ptr<T> _createModel(SceneFactory& factory, MinecraftGame& game, ClientInstance& client, const Bedrock::NotNullNonOwnerPointer<IAdvancedGraphicsOptions>& advancedGraphicOptions, const std::string& screenName, Args&&... args)
    {
        // incomplete
        MinecraftScreenModel::Context ctx{
            .mGame = game,
            .mClientInstance = client
        };
        return std::make_shared<T>(ctx, std::forward<Args>(args)...);
    }
};