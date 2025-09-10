#include "minecraft/src-client/common/client/game/ClientInstance.hpp"

// void ClientInstance::requestLeaveGame(char switchScreen, char sync) {
//     using function = void(__thiscall*)(ClientInstance*, char, char);
//     return reinterpret_cast<function>(this->vtable[13])(this, switchScreen, sync);
// }

BlockSource* ClientInstance::getRegion() {
    using function = decltype(&ClientInstance::getRegion);
    auto func = std::bit_cast<function>(this->vtable[28]);
    return (this->*func)();
}

LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = decltype(&ClientInstance::getLocalPlayer);
    auto func = std::bit_cast<function>(this->vtable[29]);
    return (this->*func)();
}

void ClientInstance::grabMouse()
{
    using function = decltype(&ClientInstance::grabMouse);
    auto func = std::bit_cast<function>(this->vtable[330]);
    return (this->*func)();
}

void ClientInstance::releaseMouse() {
    using function = decltype(&ClientInstance::releaseMouse);
    auto func = std::bit_cast<function>(this->vtable[331]);
    return (this->*func)();
}

bool ClientInstance::isShowingLoadingScreen() const
{
    using function = decltype(&ClientInstance::isShowingLoadingScreen);
    auto func = std::bit_cast<function>(this->vtable[67]);
    return (this->*func)();
}

std::shared_ptr<FileDataRequest> ClientInstance::getImageFromUrl(const std::string& imageUrl, std::function<void(Bedrock::Http::Status, const Core::Path&, uint64_t)> callback) {
    using function = decltype(&ClientInstance::getImageFromUrl);
    auto func = std::bit_cast<function>(this->vtable[360]);
    return (this->*func)(imageUrl, callback);
}

EntityId ClientInstance::getCameraEntity() const
{
    using function = decltype(&ClientInstance::getCameraEntity);
    auto func = std::bit_cast<function>(this->vtable[40]);
    return (this->*func)();
}

Actor* ClientInstance::getCameraActor() const
{
    using function = decltype(&ClientInstance::getCameraActor);
    auto func = std::bit_cast<function>(this->vtable[35]);
    return (this->*func)();
}

void ClientInstance::getRawCameraEntities(WeakEntityRef& outCamera, WeakEntityRef& outCameraTarget) const {
    using function = decltype(&ClientInstance::getRawCameraEntities);
    auto func = std::bit_cast<function>(this->vtable[41]);
    return (this->*func)(outCamera, outCameraTarget);
}

void ClientInstance::requestLeaveGame(bool switchScreen, bool sync) {
    using function = decltype(&ClientInstance::requestLeaveGame);
    auto func = std::bit_cast<function>(this->vtable[14]);
    return (this->*func)(switchScreen, sync);
}