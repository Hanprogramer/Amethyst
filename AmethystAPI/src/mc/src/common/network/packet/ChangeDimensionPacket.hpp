#pragma once
#include <mc/src/common/network/packet/Packet.hpp>
#include <mc/src-deps/core/utility/AutomaticID.hpp>
#include <mc/src/common/world/phys/Vec3.hpp>

class ChangeDimensionPacket : public Packet {
public:
    DimensionType mDimensionId;
    Vec3 mPos;
    bool mRespawn;

    // 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 8B 41 ? 48 8B FA 39 05
    virtual void write(BinaryStream&) override;
};