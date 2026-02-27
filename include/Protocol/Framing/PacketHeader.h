#pragma once
#include <cstdint>


#pragma pack(push, 1)

namespace Protocol::Framing
{
    // 모든 패킷 앞에 붙는 공통 헤더
    struct PacketHeader
    {
        // 패킷 전체 길이 (Header + Payload)
        uint16_t packetSize;
        // 메시지 ID (protobuf msg id, opcode 등)
        uint16_t messageId;
    };

}

#pragma pack(pop)

static_assert(sizeof(Protocol::Framing::PacketHeader) == 4, "PacketHeader size must be 4 bytes");
