#pragma once

#include <cstdint>

namespace se::protocol
{
    constexpr uint32_t kProtocolMagic = 0x53455256;     // 'SERV' in ASCII
    constexpr uint32_t kProtocolVersion = 18;
}   