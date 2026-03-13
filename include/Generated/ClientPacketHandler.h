#pragma once
#include "Protocol.pb.h"
#include "Protocol/Framing/PacketHeader.h"

#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
// #include "UE project use protocol header file here"
#include "CoreMinimal.h"
#include "Protocol/Framing/PacketHeader.h"
#include "Network/PacketSession.h"

#ifndef ASSERT_CRASH
    #define ASSERT_CRASH(Expr) check(Expr)
#endif
#else
#include <cassert>
#include "Network/Session/PacketSession.h"
#include "Network/Buffer/SendBuffer.h"

#ifndef ASSERT_CRASH
    #define ASSERT_CRASH(Expr) assert(Expr)
#endif
#endif

#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
using PacketSessionRef = TSharedPtr<PacketSession>;
using SendBufferRef = TSharedPtr<SendBuffer>;
#else
using PacketSessionRef = std::shared_ptr<PacketSession>;
using SendBufferRef = std::shared_ptr<SendBuffer>;
#endif

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
constexpr uint32 kMaxMessageId = UINT16_MAX;
extern PacketHandlerFunc GPacketHandler[kMaxMessageId + 1];

using PacketHeader = Protocol::Framing::PacketHeader;

enum : uint16
{
    PKT_C_HandshakeReq = 1000,
    PKT_S_HandshakeRes = 1001,
    PKT_C_LoginReq = 1010,
    PKT_S_LoginRes = 1011,
    PKT_C_Ping = 1020,
    PKT_S_Pong = 1021,
    PKT_C_LobbyEnterReq = 2000,
    PKT_S_LobbyEnterRes = 2001,
    PKT_C_MatchQueueEnterReq = 2010,
    PKT_S_MatchQueueEnterRes = 2011,
    PKT_C_MatchQueueCancelReq = 2012,
    PKT_S_MatchQueueCancelRes = 2013,
    PKT_N_MatchFound = 2020,
    PKT_S_JoinRoom = 3000,
    PKT_N_GameStart = 3020,
    PKT_C_MoveInput = 3100,
    PKT_C_AimInput = 3101,
    PKT_C_FireReq = 3110,
    PKT_S_EntityState = 3200,
    PKT_N_EntitySpawn = 3210,
    PKT_N_EntityDespawn = 3211,
    PKT_N_HitEvent = 3220,
};

// Custom packet handler declaration
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);

bool Handle_S_HandshakeRes(PacketSessionRef& session, const se::auth::S_HandshakeRes& pkt);
bool Handle_S_LoginRes(PacketSessionRef& session, const se::auth::S_LoginRes& pkt);
bool Handle_S_Pong(PacketSessionRef& session, const se::auth::S_Pong& pkt);
bool Handle_S_LobbyEnterRes(PacketSessionRef& session, const se::lobby::S_LobbyEnterRes& pkt);
bool Handle_S_MatchQueueEnterRes(PacketSessionRef& session, const se::lobby::S_MatchQueueEnterRes& pkt);
bool Handle_S_MatchQueueCancelRes(PacketSessionRef& session, const se::lobby::S_MatchQueueCancelRes& pkt);
bool Handle_N_MatchFound(PacketSessionRef& session, const se::lobby::N_MatchFound& pkt);
bool Handle_S_JoinRoom(PacketSessionRef& session, const se::room::S_JoinRoom& pkt);
bool Handle_N_GameStart(PacketSessionRef& session, const se::room::N_GameStart& pkt);
bool Handle_S_EntityState(PacketSessionRef& session, const se::room::S_EntityState& pkt);
bool Handle_N_EntitySpawn(PacketSessionRef& session, const se::room::N_EntitySpawn& pkt);
bool Handle_N_EntityDespawn(PacketSessionRef& session, const se::room::N_EntityDespawn& pkt);
bool Handle_N_HitEvent(PacketSessionRef& session, const se::room::N_HitEvent& pkt);

class ClientPacketHandler
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++) {
            GPacketHandler[i] = Handle_INVALID;
        }
        
        GPacketHandler[PKT_S_HandshakeRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::S_HandshakeRes>(Handle_S_HandshakeRes, session, buffer, len); };
        GPacketHandler[PKT_S_LoginRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::S_LoginRes>(Handle_S_LoginRes, session, buffer, len); };
        GPacketHandler[PKT_S_Pong] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::S_Pong>(Handle_S_Pong, session, buffer, len); };
        GPacketHandler[PKT_S_LobbyEnterRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_LobbyEnterRes>(Handle_S_LobbyEnterRes, session, buffer, len); };
        GPacketHandler[PKT_S_MatchQueueEnterRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_MatchQueueEnterRes>(Handle_S_MatchQueueEnterRes, session, buffer, len); };
        GPacketHandler[PKT_S_MatchQueueCancelRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_MatchQueueCancelRes>(Handle_S_MatchQueueCancelRes, session, buffer, len); };
        GPacketHandler[PKT_N_MatchFound] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::N_MatchFound>(Handle_N_MatchFound, session, buffer, len); };
        GPacketHandler[PKT_S_JoinRoom] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::S_JoinRoom>(Handle_S_JoinRoom, session, buffer, len); };
        GPacketHandler[PKT_N_GameStart] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_GameStart>(Handle_N_GameStart, session, buffer, len); };
        GPacketHandler[PKT_S_EntityState] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::S_EntityState>(Handle_S_EntityState, session, buffer, len); };
        GPacketHandler[PKT_N_EntitySpawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_EntitySpawn>(Handle_N_EntitySpawn, session, buffer, len); };
        GPacketHandler[PKT_N_EntityDespawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_EntityDespawn>(Handle_N_EntityDespawn, session, buffer, len); };
        GPacketHandler[PKT_N_HitEvent] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_HitEvent>(Handle_N_HitEvent, session, buffer, len); };
    }
    
    static SendBufferRef MakeSendBuffer(se::auth::C_HandshakeReq& pkt) { return MakeSendBuffer(pkt, PKT_C_HandshakeReq); }
    static SendBufferRef MakeSendBuffer(se::auth::C_LoginReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LoginReq); }
    static SendBufferRef MakeSendBuffer(se::auth::C_Ping& pkt) { return MakeSendBuffer(pkt, PKT_C_Ping); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_LobbyEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LobbyEnterReq); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_MatchQueueEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueEnterReq); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_MatchQueueCancelReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueCancelReq); }
    static SendBufferRef MakeSendBuffer(se::room::C_MoveInput& pkt) { return MakeSendBuffer(pkt, PKT_C_MoveInput); }
    static SendBufferRef MakeSendBuffer(se::room::C_AimInput& pkt) { return MakeSendBuffer(pkt, PKT_C_AimInput); }
    static SendBufferRef MakeSendBuffer(se::room::C_FireReq& pkt) { return MakeSendBuffer(pkt, PKT_C_FireReq); }

public:
    static bool Dispatch(PacketSessionRef& session, BYTE* buffer, int32 len)
    {
        if (len < static_cast<int32>(sizeof(PacketHeader)))
            return false;

        PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

        if (header->packetSize != len)
            return false;
            
        if (header->messageId > kMaxMessageId)
            return false;

        return GPacketHandler[header->messageId](session, buffer, len);
    }

private:
    template<typename PacketType>
    static bool HandlePacket(bool (*func)(PacketSessionRef&, const PacketType&), PacketSessionRef& session, BYTE* buffer, int32 len)
    {
        PacketType pkt;

        if (!pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)))
            return false;

        return func(session, pkt);  
    }
    
    template<typename T>
    static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
    {
        const int16 dataSize = static_cast<int32>(pkt.ByteSizeLong());
        const int16 packetSize = dataSize + sizeof(PacketHeader);
        
#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
        SendBufferRef sendBuffer = MakeShared<SendBuffer>(packetSize);
#else
        SendBufferRef sendBuffer = std::make_shared<SendBuffer>(packetSize);
#endif

        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
        header->packetSize = packetSize;
        header->messageId = pktId;
        ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
        
        sendBuffer->Close(packetSize);
        
        return sendBuffer;
    }
    
};