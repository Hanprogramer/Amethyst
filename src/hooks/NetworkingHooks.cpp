#include "hooks/NetworkingHooks.hpp"
#include "AmethystRuntime.hpp"
#include "minecraft/src/common/network/packet/Packet.hpp"
#include "minecraft/src/common/network/PacketHandlerDispatcherInstance.hpp"
#include "minecraft/src/common/network/ServerNetworkHandler.hpp"
#include "amethyst/runtime/ModContext.hpp"

class NetworkIdentifier;

SafetyHookInline _ServerNetworkHandler_allowIncomingPacketId;

bool ServerNetworkHandler_allowIncomingPacketId(ServerNetworkHandler* self, const NetworkIdentifier& networkId, MinecraftPacketIds packet)
{
    if ((int)packet == (int)MinecraftPacketIds::EndId + 1) {
    	return true;
    }
    
    return _ServerNetworkHandler_allowIncomingPacketId.call<bool, ServerNetworkHandler*, const NetworkIdentifier&, MinecraftPacketIds>(self, networkId, packet);
}

 SafetyHookInline _MinecraftPackets_createPacket;

 template <>
 class PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> : public IPacketHandlerDispatcher {
 public:
     virtual void handle(const NetworkIdentifier& networkId, NetEventCallback& netEvent, std::shared_ptr<Packet>& _packet) const override {
         std::shared_ptr<Amethyst::CustomPacketInternal>& packet = (std::shared_ptr<Amethyst::CustomPacketInternal>&)_packet;
         Amethyst::CustomPacketHandler& handler = Amethyst::GetNetworkManager().GetPacketHandler(packet->mTypeId);
         handler.handle(networkId, netEvent, *packet->mPacket.get());
     }
 };

 static PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> amethystCustomPacketHandler;

 std::shared_ptr<Packet> MinecraftPackets_createPacket(MinecraftPacketIds id) {
	// Vanilla packets.
	if (id < MinecraftPacketIds::EndId) {
        std::shared_ptr<Packet> packet = _MinecraftPackets_createPacket.call<std::shared_ptr<Packet>>(id);
		return packet;
	}

	// Custom packets
	if ((int)id == (int)MinecraftPacketIds::EndId + 1) {
		auto shared = std::make_shared<Amethyst::CustomPacketInternal>();
        shared->mHandler = &amethystCustomPacketHandler;
		return shared;
	}

    Assert(false, "MinecraftPackets::createPacket called with invalid packet id {}", (int)id);
    std::unreachable();
}

void CreateNetworkingHooks() {
    return;

    Amethyst::HookManager* hookManager = AmethystRuntime::getHookManager();

    NO_THROW_HOOK(ServerNetworkHandler, allowIncomingPacketId, "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2");
    NO_THROW_HOOK(MinecraftPackets, createPacket, "40 53 48 83 EC ? 45 33 C0 48 8B D9 FF CA 81 FA");
}