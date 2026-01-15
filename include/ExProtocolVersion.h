#pragma once
#include <cstdint>

namespace ps
{
    // 서버/클라가 이 값을 비교해서 미스매치면 즉시 에러 내면 디버깅이 쉬움
    constexpr uint16_t kProtocolVersion = 1;
    constexpr uint16_t kMagic = 0xBEEF;
}
