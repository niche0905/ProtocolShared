#pragma once
#include "Protocol.pb.h"

#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
// #include "UE project use protocol header file here"
#endif

using PacketHandlerFunc = std::function<bool(std::shared_ptr<PacketSession>&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

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
bool Handle_INVALID(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);

bool Handle_S_HandshakeRes(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_LoginRes(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_Pong(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_LobbyEnterRes(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_MatchQueueEnterRes(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_MatchQueueCancelRes(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_MatchFound(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_RoomReadyChanged(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_GameStart(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_S_EntityState(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_EntitySpawn(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_EntityDespawn(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);
bool Handle_N_HitEvent(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);

class ClientPacketHandler
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++) {
            GPacketHandler[i] = Handle_INVALID;
        }
        
        GPacketHandler[PKT_S_HandshakeRes] = Handle_S_HandshakeRes;
        GPacketHandler[PKT_S_LoginRes] = Handle_S_LoginRes;
        GPacketHandler[PKT_S_Pong] = Handle_S_Pong;
        GPacketHandler[PKT_S_LobbyEnterRes] = Handle_S_LobbyEnterRes;
        GPacketHandler[PKT_S_MatchQueueEnterRes] = Handle_S_MatchQueueEnterRes;
        GPacketHandler[PKT_S_MatchQueueCancelRes] = Handle_S_MatchQueueCancelRes;
        GPacketHandler[PKT_N_MatchFound] = Handle_N_MatchFound;
        GPacketHandler[PKT_N_RoomReadyChanged] = Handle_N_RoomReadyChanged;
        GPacketHandler[PKT_N_GameStart] = Handle_N_GameStart;
        GPacketHandler[PKT_S_EntityState] = Handle_S_EntityState;
        GPacketHandler[PKT_N_EntitySpawn] = Handle_N_EntitySpawn;
        GPacketHandler[PKT_N_EntityDespawn] = Handle_N_EntityDespawn;
        GPacketHandler[PKT_N_HitEvent] = Handle_N_HitEvent;
    }
    
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::AUTH::C_HandshakeReq& pkt) { return MakeSendBuffer(pkt, PKT_C_HandshakeReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::AUTH::C_LoginReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LoginReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::AUTH::C_Ping& pkt) { return MakeSendBuffer(pkt, PKT_C_Ping); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::LOBBY::C_LobbyEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LobbyEnterReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::LOBBY::C_MatchQueueEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueEnterReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::LOBBY::C_MatchQueueCancelReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueCancelReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::ROOM::C_RoomReadyReq& pkt) { return MakeSendBuffer(pkt, PKT_C_RoomReadyReq); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::ROOM::C_MoveInput& pkt) { return MakeSendBuffer(pkt, PKT_C_MoveInput); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::ROOM::C_AimInput& pkt) { return MakeSendBuffer(pkt, PKT_C_AimInput); }
    static std::shared_ptr<SendBuffer> MakeSendBuffer(SE::ROOM::C_FireReq& pkt) { return MakeSendBuffer(pkt, PKT_C_FireReq); }

private:
    template<typename PacketType, typename ProcessFunc>
    static bool HandlePacket(ProcessFunc func, std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len)
    {
        PacketType pkt;
        if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false) {
            return false;
        }
        return func(session, pkt);
    }
    
    template<typename T>
    static std::shared_ptr<SendBuffer> MakeSendBuffer(T& pkt, uint16 pktId)
    {
        const int16 dataSize = static_cast<int32>(pkt.ByteSizeLong());
        const int16 packetSize = dataSize + sizeof(PacketHeader);
        
#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1
        TSharedPtr<SendBuffer> sendBuffer = MakeShared<SendBuffer>(packetSize);
#else
        std::shared_ptr<SendBuffer> sendBuffer = std::make_shared<SendBuffer>(packetSize);
#endif

        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
        header->size = packetSize;
        header->id = pktId;
        ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
        
        sendBuffer->Close(packetSize);
        
        return sendBuffer;
    }
    
};