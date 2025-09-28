#pragma once
#include <mc/src/common/network/packet/Packet.hpp>
#include <mc/src/common/nbt/CompoundTagVariant.hpp>
#include <mc/src/common/nbt/CompoundTag.hpp>
#include <mc/src/common/network/NetworkBlockPosition.hpp>

class BlockActorDataPacket : public Packet {
public:
    NetworkBlockPosition mPos;
    CompoundTag mData;
};