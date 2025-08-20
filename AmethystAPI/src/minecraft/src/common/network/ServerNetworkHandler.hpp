#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/CommonTypes.hpp>

class ServerPlayer;
class ILevel;
class NetworkIdentifier;
class LoginPacket;
class RequestNetworkSettingsPacket;

class ServerNetworkHandler {
public:
    /* this + 8  */ std::byte padding8[80];
    /* this + 88 */ Bedrock::NonOwnerPointer<ILevel> mLevel;

public:
    virtual ~ServerNetworkHandler();
    virtual void unknown1();

    // virtuals: cba to deal with virtual inheritance
    ServerPlayer* _getServerPlayer(const NetworkIdentifier& source, SubClientId subId) {
        using function = decltype(&ServerNetworkHandler::_getServerPlayer);
        static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B 41 ? 41 0F B6 E8"));
        return (this->*func)(source, subId);
    }
};

static_assert(offsetof(ServerNetworkHandler, mLevel) == 88);