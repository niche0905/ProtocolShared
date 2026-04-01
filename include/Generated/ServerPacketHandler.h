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
    PKT_C_SetNicknameReq = 2002,
    PKT_S_SetNicknameRes = 2003,
    PKT_C_MatchQueueEnterReq = 2010,
    PKT_S_MatchQueueEnterRes = 2011,
    PKT_C_MatchQueueCancelReq = 2012,
    PKT_S_MatchQueueCancelRes = 2013,
    PKT_N_MatchFound = 2020,
    PKT_C_RoomEnterReq = 3000,
    PKT_S_RoomEnterRes = 3001,
    PKT_C_RoomLeaveReq = 3010,
    PKT_S_RoomLeaveRes = 3011,
    PKT_N_EntitySpawn = 3100,
    PKT_N_EntityDespawn = 3101,
    PKT_N_RoomClosed = 3200,
    PKT_C_LoadingCompleteReq = 4000,
    PKT_N_GameStart = 4001,
    PKT_N_GameEnd = 4002,
    PKT_C_MoveReq = 4010,
    PKT_N_Move = 4011,
    PKT_C_JumpReq = 4020,
    PKT_N_Jump = 4021,
    PKT_C_JumpLand = 4022,
    PKT_N_JumpLand = 4023,
    PKT_C_CrouchReq = 4030,
    PKT_N_Crouch = 4031,
    PKT_C_WireActionReq = 4040,
    PKT_N_WireAction = 4041,
    PKT_C_WireActionEnd = 4042,
    PKT_N_WireActionEnd = 4043,
    PKT_C_AimReq = 4090,
    PKT_N_Aim = 4091,
    PKT_C_FireReq = 4100,
    PKT_N_Fire = 4101,
    PKT_C_AttackReq = 4102,
    PKT_N_Attack = 4103,
    PKT_C_ThrowGrenadeReq = 4104,
    PKT_N_ThrowGrenade = 4105,
    PKT_C_ReloadReq = 4106,
    PKT_N_Reload = 4107,
    PKT_C_WeaponChangeReq = 4108,
    PKT_N_WeaponChanged = 4109,
    PKT_C_UseAbilityReq = 4110,
    PKT_N_UseAbility = 4111,
    PKT_N_KillPlayer = 4112,
    PKT_C_UseItemReq = 4200,
    PKT_N_UseItem = 4201,
    PKT_C_ChestInteractReq = 4202,
    PKT_C_PickupItemReq = 4203,
    PKT_N_PickupItem = 4204,
    PKT_C_UseStoreReq = 4205,
    PKT_S_UseStoreRes = 4206,
    PKT_N_ItemGained = 4207,
    PKT_C_SetSavePointReq = 4208,
    PKT_N_HealthChanged = 4300,
    PKT_N_EntityDied = 4301,
    PKT_N_EntityRespawned = 4302,
    PKT_N_EntityDestroyed = 4303,
    PKT_N_TimePointChanged = 4304,
    PKT_N_TimeStormChange = 4400,
};

// Custom packet handler declaration
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);

bool Handle_C_HandshakeReq(PacketSessionRef& session, const se::auth::C_HandshakeReq& pkt);
bool Handle_C_LoginReq(PacketSessionRef& session, const se::auth::C_LoginReq& pkt);
bool Handle_C_Ping(PacketSessionRef& session, const se::auth::C_Ping& pkt);
bool Handle_C_SetNicknameReq(PacketSessionRef& session, const se::lobby::C_SetNicknameReq& pkt);
bool Handle_C_MatchQueueEnterReq(PacketSessionRef& session, const se::lobby::C_MatchQueueEnterReq& pkt);
bool Handle_C_MatchQueueCancelReq(PacketSessionRef& session, const se::lobby::C_MatchQueueCancelReq& pkt);
bool Handle_C_RoomEnterReq(PacketSessionRef& session, const se::room::C_RoomEnterReq& pkt);
bool Handle_C_RoomLeaveReq(PacketSessionRef& session, const se::room::C_RoomLeaveReq& pkt);
bool Handle_C_LoadingCompleteReq(PacketSessionRef& session, const se::game::C_LoadingCompleteReq& pkt);
bool Handle_C_MoveReq(PacketSessionRef& session, const se::game::C_MoveReq& pkt);
bool Handle_C_JumpReq(PacketSessionRef& session, const se::game::C_JumpReq& pkt);
bool Handle_C_JumpLand(PacketSessionRef& session, const se::game::C_JumpLand& pkt);
bool Handle_C_CrouchReq(PacketSessionRef& session, const se::game::C_CrouchReq& pkt);
bool Handle_C_WireActionReq(PacketSessionRef& session, const se::game::C_WireActionReq& pkt);
bool Handle_C_WireActionEnd(PacketSessionRef& session, const se::game::C_WireActionEnd& pkt);
bool Handle_C_AimReq(PacketSessionRef& session, const se::game::C_AimReq& pkt);
bool Handle_C_FireReq(PacketSessionRef& session, const se::game::C_FireReq& pkt);
bool Handle_C_AttackReq(PacketSessionRef& session, const se::game::C_AttackReq& pkt);
bool Handle_C_ThrowGrenadeReq(PacketSessionRef& session, const se::game::C_ThrowGrenadeReq& pkt);
bool Handle_C_ReloadReq(PacketSessionRef& session, const se::game::C_ReloadReq& pkt);
bool Handle_C_WeaponChangeReq(PacketSessionRef& session, const se::game::C_WeaponChangeReq& pkt);
bool Handle_C_UseAbilityReq(PacketSessionRef& session, const se::game::C_UseAbilityReq& pkt);
bool Handle_C_UseItemReq(PacketSessionRef& session, const se::game::C_UseItemReq& pkt);
bool Handle_C_ChestInteractReq(PacketSessionRef& session, const se::game::C_ChestInteractReq& pkt);
bool Handle_C_PickupItemReq(PacketSessionRef& session, const se::game::C_PickupItemReq& pkt);
bool Handle_C_UseStoreReq(PacketSessionRef& session, const se::game::C_UseStoreReq& pkt);
bool Handle_C_SetSavePointReq(PacketSessionRef& session, const se::game::C_SetSavePointReq& pkt);

class ServerPacketHandler
{
public:
    static void Init()
    {
        for (int32 i = 0; i < UINT16_MAX; i++) {
            GPacketHandler[i] = Handle_INVALID;
        }
        
        GPacketHandler[PKT_C_HandshakeReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::C_HandshakeReq>(Handle_C_HandshakeReq, session, buffer, len); };
        GPacketHandler[PKT_C_LoginReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::C_LoginReq>(Handle_C_LoginReq, session, buffer, len); };
        GPacketHandler[PKT_C_Ping] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::auth::C_Ping>(Handle_C_Ping, session, buffer, len); };
        GPacketHandler[PKT_C_SetNicknameReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::C_SetNicknameReq>(Handle_C_SetNicknameReq, session, buffer, len); };
        GPacketHandler[PKT_C_MatchQueueEnterReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::C_MatchQueueEnterReq>(Handle_C_MatchQueueEnterReq, session, buffer, len); };
        GPacketHandler[PKT_C_MatchQueueCancelReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::C_MatchQueueCancelReq>(Handle_C_MatchQueueCancelReq, session, buffer, len); };
        GPacketHandler[PKT_C_RoomEnterReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::C_RoomEnterReq>(Handle_C_RoomEnterReq, session, buffer, len); };
        GPacketHandler[PKT_C_RoomLeaveReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::C_RoomLeaveReq>(Handle_C_RoomLeaveReq, session, buffer, len); };
        GPacketHandler[PKT_C_LoadingCompleteReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_LoadingCompleteReq>(Handle_C_LoadingCompleteReq, session, buffer, len); };
        GPacketHandler[PKT_C_MoveReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_MoveReq>(Handle_C_MoveReq, session, buffer, len); };
        GPacketHandler[PKT_C_JumpReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_JumpReq>(Handle_C_JumpReq, session, buffer, len); };
        GPacketHandler[PKT_C_JumpLand] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_JumpLand>(Handle_C_JumpLand, session, buffer, len); };
        GPacketHandler[PKT_C_CrouchReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_CrouchReq>(Handle_C_CrouchReq, session, buffer, len); };
        GPacketHandler[PKT_C_WireActionReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WireActionReq>(Handle_C_WireActionReq, session, buffer, len); };
        GPacketHandler[PKT_C_WireActionEnd] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WireActionEnd>(Handle_C_WireActionEnd, session, buffer, len); };
        GPacketHandler[PKT_C_AimReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_AimReq>(Handle_C_AimReq, session, buffer, len); };
        GPacketHandler[PKT_C_FireReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_FireReq>(Handle_C_FireReq, session, buffer, len); };
        GPacketHandler[PKT_C_AttackReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_AttackReq>(Handle_C_AttackReq, session, buffer, len); };
        GPacketHandler[PKT_C_ThrowGrenadeReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ThrowGrenadeReq>(Handle_C_ThrowGrenadeReq, session, buffer, len); };
        GPacketHandler[PKT_C_ReloadReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ReloadReq>(Handle_C_ReloadReq, session, buffer, len); };
        GPacketHandler[PKT_C_WeaponChangeReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WeaponChangeReq>(Handle_C_WeaponChangeReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseAbilityReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseAbilityReq>(Handle_C_UseAbilityReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseItemReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseItemReq>(Handle_C_UseItemReq, session, buffer, len); };
        GPacketHandler[PKT_C_ChestInteractReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ChestInteractReq>(Handle_C_ChestInteractReq, session, buffer, len); };
        GPacketHandler[PKT_C_PickupItemReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_PickupItemReq>(Handle_C_PickupItemReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseStoreReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseStoreReq>(Handle_C_UseStoreReq, session, buffer, len); };
        GPacketHandler[PKT_C_SetSavePointReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_SetSavePointReq>(Handle_C_SetSavePointReq, session, buffer, len); };
    }
    
    static SendBufferRef MakeSendBuffer(se::auth::S_HandshakeRes& pkt) { return MakeSendBuffer(pkt, PKT_S_HandshakeRes); }
    static SendBufferRef MakeSendBuffer(se::auth::S_LoginRes& pkt) { return MakeSendBuffer(pkt, PKT_S_LoginRes); }
    static SendBufferRef MakeSendBuffer(se::auth::S_Pong& pkt) { return MakeSendBuffer(pkt, PKT_S_Pong); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_SetNicknameRes& pkt) { return MakeSendBuffer(pkt, PKT_S_SetNicknameRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_MatchQueueEnterRes& pkt) { return MakeSendBuffer(pkt, PKT_S_MatchQueueEnterRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::S_MatchQueueCancelRes& pkt) { return MakeSendBuffer(pkt, PKT_S_MatchQueueCancelRes); }
    static SendBufferRef MakeSendBuffer(se::lobby::N_MatchFound& pkt) { return MakeSendBuffer(pkt, PKT_N_MatchFound); }
    static SendBufferRef MakeSendBuffer(se::room::S_RoomEnterRes& pkt) { return MakeSendBuffer(pkt, PKT_S_RoomEnterRes); }
    static SendBufferRef MakeSendBuffer(se::room::S_RoomLeaveRes& pkt) { return MakeSendBuffer(pkt, PKT_S_RoomLeaveRes); }
    static SendBufferRef MakeSendBuffer(se::room::N_EntitySpawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntitySpawn); }
    static SendBufferRef MakeSendBuffer(se::room::N_EntityDespawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDespawn); }
    static SendBufferRef MakeSendBuffer(se::room::N_RoomClosed& pkt) { return MakeSendBuffer(pkt, PKT_N_RoomClosed); }
    static SendBufferRef MakeSendBuffer(se::game::N_GameStart& pkt) { return MakeSendBuffer(pkt, PKT_N_GameStart); }
    static SendBufferRef MakeSendBuffer(se::game::N_GameEnd& pkt) { return MakeSendBuffer(pkt, PKT_N_GameEnd); }
    static SendBufferRef MakeSendBuffer(se::game::N_Move& pkt) { return MakeSendBuffer(pkt, PKT_N_Move); }
    static SendBufferRef MakeSendBuffer(se::game::N_Jump& pkt) { return MakeSendBuffer(pkt, PKT_N_Jump); }
    static SendBufferRef MakeSendBuffer(se::game::N_JumpLand& pkt) { return MakeSendBuffer(pkt, PKT_N_JumpLand); }
    static SendBufferRef MakeSendBuffer(se::game::N_Crouch& pkt) { return MakeSendBuffer(pkt, PKT_N_Crouch); }
    static SendBufferRef MakeSendBuffer(se::game::N_WireAction& pkt) { return MakeSendBuffer(pkt, PKT_N_WireAction); }
    static SendBufferRef MakeSendBuffer(se::game::N_WireActionEnd& pkt) { return MakeSendBuffer(pkt, PKT_N_WireActionEnd); }
    static SendBufferRef MakeSendBuffer(se::game::N_Aim& pkt) { return MakeSendBuffer(pkt, PKT_N_Aim); }
    static SendBufferRef MakeSendBuffer(se::game::N_Fire& pkt) { return MakeSendBuffer(pkt, PKT_N_Fire); }
    static SendBufferRef MakeSendBuffer(se::game::N_Attack& pkt) { return MakeSendBuffer(pkt, PKT_N_Attack); }
    static SendBufferRef MakeSendBuffer(se::game::N_ThrowGrenade& pkt) { return MakeSendBuffer(pkt, PKT_N_ThrowGrenade); }
    static SendBufferRef MakeSendBuffer(se::game::N_Reload& pkt) { return MakeSendBuffer(pkt, PKT_N_Reload); }
    static SendBufferRef MakeSendBuffer(se::game::N_WeaponChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_WeaponChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_UseAbility& pkt) { return MakeSendBuffer(pkt, PKT_N_UseAbility); }
    static SendBufferRef MakeSendBuffer(se::game::N_KillPlayer& pkt) { return MakeSendBuffer(pkt, PKT_N_KillPlayer); }
    static SendBufferRef MakeSendBuffer(se::game::N_UseItem& pkt) { return MakeSendBuffer(pkt, PKT_N_UseItem); }
    static SendBufferRef MakeSendBuffer(se::game::N_PickupItem& pkt) { return MakeSendBuffer(pkt, PKT_N_PickupItem); }
    static SendBufferRef MakeSendBuffer(se::game::S_UseStoreRes& pkt) { return MakeSendBuffer(pkt, PKT_S_UseStoreRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_ItemGained& pkt) { return MakeSendBuffer(pkt, PKT_N_ItemGained); }
    static SendBufferRef MakeSendBuffer(se::game::N_HealthChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_HealthChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityDied& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDied); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityRespawned& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityRespawned); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityDestroyed& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDestroyed); }
    static SendBufferRef MakeSendBuffer(se::game::N_TimePointChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_TimePointChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_TimeStormChange& pkt) { return MakeSendBuffer(pkt, PKT_N_TimeStormChange); }

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