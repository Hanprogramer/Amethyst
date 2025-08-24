#include <utility>

#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include "amethyst/runtime/input/InputAction.hpp"
#include "minecraft/src-client/common/client/game/IClientInstance.hpp"

Amethyst::InputManager::InputManager(AmethystContext *amethyst) {
    mAmethyst = amethyst;
}

//void Amethyst::InputManager::RegisterNewInput(
//        std::string actionName,
//        std::vector<int> keys,
//        bool allowRemapping
//){
//    Options* opt = mAmethyst->mOptions;
//    Assert(opt, "AmethystContext->mOptions was null, ensure that RegisterNewInput is being called in the RegisterInputs event.");
//    
//
//    for (auto& layout : opt->mKeyboardRemappings)
//    {
//        Keymapping keymapping("key." + actionName, keys, allowRemapping);
//        layout->mKeymappings.emplace_back(keymapping);
//        layout->mDefaultMappings.emplace_back(keymapping);
//    }
//
//    mRegisteredInputs.emplace_back(actionName);
//}

Amethyst::InputManager::~InputManager() {
    Options* opt = mAmethyst->mOptions;

    // Remove registered keys.
    //for (auto& actionName : mRegisteredInputs) {
    //    for (auto& mapping : opt->mKeyboardRemappings) {
    //        auto newEnd = std::remove_if(
    //            mapping->mKeymappings.begin(),
    //            mapping->mKeymappings.end(),
    //            [&actionName](const Keymapping& keymapping)
    //        {
    //              return keymapping.mAction == std::string("key." + actionName);
    //        });

    //        // Erase the removed elements from the vector.
    //        mapping->mKeymappings.erase(newEnd, mapping->mKeymappings.end());
    //    }
    //}

    //mRegisteredInputs.clear();
}

Amethyst::InputAction& Amethyst::InputManager::RegisterNewInput(const std::string& actionName, std::vector<int> defaultKeys, bool allowRemapping, KeybindContext context)
{
    uint32_t hash = StringToNameId("button." + actionName);

    // Look for an existing listner with the same name.
    auto it = mActions.find(hash);
    if (it != mActions.end()) {
        return *(it->second);
    }

    auto action = std::make_unique<Amethyst::InputAction>(actionName);
    auto [newIt, _] = mActions.emplace(hash, std::move(action));
    return *(newIt->second);
}

Amethyst::InputAction& Amethyst::InputManager::GetVanillaInput(const std::string& actionName)
{
    uint32_t hash = StringToNameId("button." + actionName);

    // Look for an existing listner with the same name.
    auto it = mActions.find(hash);
    if (it != mActions.end()) {
        return *(it->second);
    }

    auto action = std::make_unique<Amethyst::InputAction>(actionName);
    auto [newIt, _] = mActions.emplace(hash, std::move(action));
    return *(newIt->second);
}

void Amethyst::InputManager::_handleButtonEvent(InputHandler* handler, const ButtonEventData& button, FocusImpact focus, IClientInstance& client, int controllerId) const
{
    auto it = mActions.find(button.id);
    Log::Info("_handleButtonEvent: button id {}", button.id);

    if (it == mActions.end()) {
        Log::Info("Not found...");
        return;
    }

    const Amethyst::InputAction& action = *it->second.get();
    Log::Info("found!!");
    action._onButtonStateChange(button.state, focus, client);

}

//void Amethyst::InputManager::AddButtonDownHandler(
//        const std::string& actionName,
//        std::function<void(FocusImpact, IClientInstance &)> handler,
//        bool suspendable)
//{
//    ClientInputHandler* clientInput = mAmethyst->mClientInstance->inputHandler;
//    Assert(clientInput != nullptr, "ButtonHandlers cannot be created in amethyst event RegisterInputs, consider using OnStartJoinGame.");
//    
//
//    InputHandler* inputHandler = clientInput->mInputHandler;
//    inputHandler->registerButtonDownHandler("button." + actionName, std::move(handler), suspendable);
//}

//void Amethyst::InputManager::AddButtonUpHandler(
//        const std::string &actionName,
//        std::function<void(FocusImpact, IClientInstance &)> handler,
//        bool suspendable)
//{
//    ClientInputHandler* clientInput = mAmethyst->mClientInstance->inputHandler;
//    Assert(clientInput != nullptr, "ButtonHandlers cannot be created in amethyst event RegisterInputs, consider using OnStartJoinGame.");
//
//    InputHandler* inputHandler = clientInput->mInputHandler;
//    inputHandler->registerButtonUpHandler("button." + actionName, std::move(handler), suspendable);
//}
//
//void Amethyst::InputManager::RemoveButtonHandlers() {
//    InputHandler* mcInput = mAmethyst->mClientInstance->inputHandler->mInputHandler;
//
//    // Remove button down listeners
//    for (auto& actionName : mRegisteredInputs) {
//        uint32_t actionId = StringToNameId("button." + actionName);
//
//        auto it = mcInput->mButtonDownHandlerMap.begin();
//        while (it != mcInput->mButtonDownHandlerMap.end()) {
//            if (it->first == actionId) {
//                it = mcInput->mButtonDownHandlerMap.erase(it);
//                continue;
//            }
//            ++it;
//        }
//
//        it = mcInput->mButtonUpHandlerMap.begin();
//        while (it != mcInput->mButtonUpHandlerMap.end()) {
//            if (it->first == actionId) {
//                it = mcInput->mButtonUpHandlerMap.erase(it);
//                continue;
//            }
//            ++it;
//        }
//    }
//}
