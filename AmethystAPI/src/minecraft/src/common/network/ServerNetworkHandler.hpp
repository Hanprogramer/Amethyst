/// @symbolgeneration
#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/CommonTypes.hpp>
#include <minecraft/src/common/world/level/LevelListener.hpp>
#include <minecraft/src-deps/core/threading/EnableQueueForMainThread.hpp>
#include <minecraft/src/common/network/NetEventCallback.hpp>
#include <minecraft/src/common/network/packet/Packet.hpp>

class ServerPlayer;
class ILevel;
class NetworkIdentifier;
class LoginPacket;
class RequestNetworkSettingsPacket;

namespace Social {
class MultiplayerServiceObserver {
public:
    virtual ~MultiplayerServiceObserver() = default;
    virtual void padding0_eagfeg();
};

class XboxLiveUserObserver {
public:
    virtual ~XboxLiveUserObserver() = default;
    virtual void padding0_afdefe();
}; 
}

class ServerNetworkHandler : public Bedrock::Threading::EnableQueueForMainThread, public NetEventCallback, public LevelListener, public Social::MultiplayerServiceObserver, public Social::XboxLiveUserObserver {
public:
    /*  */ std::byte padding32[56];
    /* this + 88 */ Bedrock::NonOwnerPointer<ILevel> mLevel;

public:
    virtual ~ServerNetworkHandler();

    // virtuals: cba to deal with virtual inheritance
    virtual ServerPlayer* _getServerPlayer(const NetworkIdentifier& source, SubClientId subId);

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2}
    MC bool allowIncomingPacketId(const NetworkIdentifier& networkId, MinecraftPacketIds packet);
};
 
//static_assert(offsetof(ServerNetworkHandler, mLevel) == 88);