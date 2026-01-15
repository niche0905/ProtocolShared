#pragma once
#include <cstdint>

namespace ps // ProtocolShared
{
    // PacketId는 서버/클라가 반드시 동일해야 함
    enum class PacketId : uint16_t
    {
        // System
        C2S_LoginReq = 1001,
        S2C_LoginRes = 1002,

        C2S_Ping     = 1101,
        S2C_Pong     = 1102,
    };
}
