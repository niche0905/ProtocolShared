#pragma once
#include "Protocol.pb.h"

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
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

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
    PKT_C_RoomReadyReq = 3010,
    PKT_N_RoomReadyChanged = 3011,
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

bool Handle_C_HandshakeReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_LoginReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_Ping(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_LobbyEnterReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_MatchQueueEnterReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_MatchQueueCancelReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_RoomReadyReq(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_MoveInput(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_AimInput(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_FireReq(PacketSessionRef& session, BYTE* buffer, int32 len);

class ServerPacketHandler
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++) {
            GPacketHandler[i] = Handle_INVALID;
        }
        
        GPacketHandler[PKT_C_HandshakeReq] = Handle_C_HandshakeReq;
        GPacketHandler[PKT_C_LoginReq] = Handle_C_LoginReq;
        GPacketHandler[PKT_C_Ping] = Handle_C_Ping;
        GPacketHandler[PKT_C_LobbyEnterReq] = Handle_C_LobbyEnterReq;
        GPacketHandler[PKT_C_MatchQueueEnterReq] = Handle_C_MatchQueueEnterReq;
        GPacketHandler[PKT_C_MatchQueueCancelReq] = Handle_C_MatchQueueCancelReq;
        GPacketHandler[PKT_C_RoomReadyReq] = Handle_C_RoomReadyReq;
        GPacketHandler[PKT_C_MoveInput] = Handle_C_MoveInput;
        GPacketHandler[PKT_C_AimInput] = Handle_C_AimInput;
        GPacketHandler[PKT_C_FireReq] = Handle_C_FireReq;
    }
    
    static SendBufferRef MakeSendBuffer(se::auth::S_HandshakeRes& pkt) { return MakeSendBuffer(pkt, PKT_S_HandshakeRes); }
    static SendBufferRef MakeSendBuffer(se::auth::S_LoginRes& pkt) { return MakeSendBuffer(pkt, PKT_S_LoginRes); }
    static SendBufferRef MakeSendBuffer(se::auth::S_Pong& pkt) { return MakeSendBuffer(pkt, PKT_S_Pong); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_LobbyEnterRes& pkt) { return MakeSendBuffer(pkt, PKT_S_LobbyEnterRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_MatchQueueEnterRes& pkt) { return MakeSendBuffer(pkt, PKT_S_MatchQueueEnterRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_MatchQueueCancelRes& pkt) { return MakeSendBuffer(pkt, PKT_S_MatchQueueCancelRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::N_MatchFound& pkt) { return MakeSendBuffer(pkt, PKT_N_MatchFound); }
    static SendBufferRef MakeSendBuffer(se::room::N_RoomReadyChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_RoomReadyChanged); }
    static SendBufferRef MakeSendBuffer(se::room::N_GameStart& pkt) { return MakeSendBuffer(pkt, PKT_N_GameStart); }
    static SendBufferRef MakeSendBuffer(se::room::S_EntityState& pkt) { return MakeSendBuffer(pkt, PKT_S_EntityState); }
    static SendBufferRef MakeSendBuffer(se::room::N_EntitySpawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntitySpawn); }
    static SendBufferRef MakeSendBuffer(se::room::N_EntityDespawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDespawn); }
    static SendBufferRef MakeSendBuffer(se::room::N_HitEvent& pkt) { return MakeSendBuffer(pkt, PKT_N_HitEvent); }

public:
    static bool Dispatch(PacketSessionRef& session, BYTE* buffer, int32 len)
    {
        if (len < static_cast<int32>(sizeof(PacketHeader)))
            return false;

        PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

        if (header->packetSize != len)
            return false;

        return GPacketHandler[header->messageId](session, buffer, len);
    }

private:
    template<typename PacketType, typename ProcessFunc>
    static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
    {
        PacketType pkt;
        if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false) {
            return false;
        }
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