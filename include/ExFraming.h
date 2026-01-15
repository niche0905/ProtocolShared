#pragma once
#include <cstdint>
#include <cstring>
#include "PacketIds.h"

namespace ps
{
#pragma pack(push, 1)

    // 네트워크 바이트 스트림에서 앞에 붙는 공통 헤더
    // (Protobuf payload는 이 헤더 뒤에 온다고 가정)
    struct PacketHeader
    {
        uint16_t magic = 0xBEEF;     // 동기화/검증용
        uint16_t version = 1;        // 프로토콜 버전
        uint16_t header_size = sizeof(PacketHeader);
        uint16_t packet_id = 0;      // ps::PacketId 값
        uint32_t payload_size = 0;   // protobuf bytes 크기
        uint32_t reserved = 0;       // flags/seq 등으로 확장 가능
    };

#pragma pack(pop)

    inline bool ValidateHeaderBasic(const PacketHeader& h)
    {
        if (h.magic != 0xBEEF) return false;
        if (h.header_size != sizeof(PacketHeader)) return false;
        // version 체크는 서버/클라 정책에 따라
        return true;
    }

    // 안전하게 PacketId 저장 (enum → uint16_t)
    inline void SetPacketId(PacketHeader& h, PacketId id)
    {
        h.packet_id = static_cast<uint16_t>(id);
    }
}
