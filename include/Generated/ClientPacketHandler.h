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

// 서버 빌드에서만 필요
class ServerPacketDispatcher;

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

#if !(UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING >= 1)
void SetServerPacketDispatcher(ServerPacketDispatcher* dispatcher);
ServerPacketDispatcher* GetServerPacketDispatcher();
#endif

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
    PKT_S_RoomSetupEnd = 3102,
    PKT_N_EntitiesSpawn = 3103,
    PKT_N_RoomClosed = 3200,
    PKT_C_LoadingCompleteReq = 4000,
    PKT_N_GameStart = 4001,
    PKT_N_GameEnd = 4002,
    PKT_N_PlayerInitSetup = 4003,
    PKT_C_MoveReq = 4010,
    PKT_N_Move = 4011,
    PKT_C_JumpReq = 4020,
    PKT_N_Jump = 4021,
    PKT_C_JumpLand = 4022,
    PKT_N_JumpLand = 4023,
    PKT_C_DoubleJumpReq = 4024,
    PKT_N_DoubleJump = 4025,
    PKT_C_CrouchReq = 4030,
    PKT_N_Crouch = 4031,
    PKT_C_WireActionReq = 4040,
    PKT_N_WireAction = 4041,
    PKT_C_WireActionEnd = 4042,
    PKT_N_WireActionEnd = 4043,
    PKT_C_WireLaunchReq = 4044,
    PKT_N_WireLaunch = 4045,
    PKT_C_AimReq = 4090,
    PKT_N_Aim = 4091,
    PKT_C_FireReq = 4100,
    PKT_N_Fire = 4101,
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
    PKT_S_ReloadRes = 4113,
    PKT_N_EntityHit = 4114,
    PKT_N_WeaponStatChanged = 4115,
    PKT_C_UseItemReq = 4200,
    PKT_N_UseItem = 4201,
    PKT_C_ChestInteractReq = 4202,
    PKT_C_PickupItemReq = 4203,
    PKT_N_PickupItem = 4204,
    PKT_C_UseStoreReq = 4205,
    PKT_S_UseStoreRes = 4206,
    PKT_N_ItemGained = 4207,
    PKT_C_SetSavePointReq = 4209,
    PKT_S_UseItemRes = 4210,
    PKT_S_SetSavePointRes = 4211,
    PKT_N_ChestInteracted = 4212,
    PKT_N_ItemLost = 4213,
    PKT_C_EquipItemReq = 4214,
    PKT_N_EquipItem = 4215,
    PKT_S_EquipItemRes = 4216,
    PKT_N_HealthChanged = 4300,
    PKT_N_EntityDied = 4301,
    PKT_N_EntityRespawned = 4302,
    PKT_N_EntityDestroyed = 4303,
    PKT_N_TimePointChanged = 4304,
    PKT_N_MaxHealthChanged = 4305,
    PKT_N_TimeStormChange = 4400,
};

// Custom packet handler declaration
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);

bool Handle_S_HandshakeRes(PacketSessionRef& session, const se::auth::S_HandshakeRes& pkt);
bool Handle_S_LoginRes(PacketSessionRef& session, const se::auth::S_LoginRes& pkt);
bool Handle_S_Pong(PacketSessionRef& session, const se::auth::S_Pong& pkt);
bool Handle_S_SetNicknameRes(PacketSessionRef& session, const se::lobby::S_SetNicknameRes& pkt);
bool Handle_S_MatchQueueEnterRes(PacketSessionRef& session, const se::lobby::S_MatchQueueEnterRes& pkt);
bool Handle_S_MatchQueueCancelRes(PacketSessionRef& session, const se::lobby::S_MatchQueueCancelRes& pkt);
bool Handle_N_MatchFound(PacketSessionRef& session, const se::lobby::N_MatchFound& pkt);
bool Handle_S_RoomEnterRes(PacketSessionRef& session, const se::room::S_RoomEnterRes& pkt);
bool Handle_S_RoomLeaveRes(PacketSessionRef& session, const se::room::S_RoomLeaveRes& pkt);
bool Handle_N_EntitySpawn(PacketSessionRef& session, const se::room::N_EntitySpawn& pkt);
bool Handle_N_EntityDespawn(PacketSessionRef& session, const se::room::N_EntityDespawn& pkt);
bool Handle_S_RoomSetupEnd(PacketSessionRef& session, const se::room::S_RoomSetupEnd& pkt);
bool Handle_N_EntitiesSpawn(PacketSessionRef& session, const se::room::N_EntitiesSpawn& pkt);
bool Handle_N_RoomClosed(PacketSessionRef& session, const se::room::N_RoomClosed& pkt);
bool Handle_N_GameStart(PacketSessionRef& session, const se::game::N_GameStart& pkt);
bool Handle_N_GameEnd(PacketSessionRef& session, const se::game::N_GameEnd& pkt);
bool Handle_N_PlayerInitSetup(PacketSessionRef& session, const se::game::N_PlayerInitSetup& pkt);
bool Handle_N_Move(PacketSessionRef& session, const se::game::N_Move& pkt);
bool Handle_N_Jump(PacketSessionRef& session, const se::game::N_Jump& pkt);
bool Handle_N_JumpLand(PacketSessionRef& session, const se::game::N_JumpLand& pkt);
bool Handle_N_DoubleJump(PacketSessionRef& session, const se::game::N_DoubleJump& pkt);
bool Handle_N_Crouch(PacketSessionRef& session, const se::game::N_Crouch& pkt);
bool Handle_N_WireAction(PacketSessionRef& session, const se::game::N_WireAction& pkt);
bool Handle_N_WireActionEnd(PacketSessionRef& session, const se::game::N_WireActionEnd& pkt);
bool Handle_N_WireLaunch(PacketSessionRef& session, const se::game::N_WireLaunch& pkt);
bool Handle_N_Aim(PacketSessionRef& session, const se::game::N_Aim& pkt);
bool Handle_N_Fire(PacketSessionRef& session, const se::game::N_Fire& pkt);
bool Handle_N_Attack(PacketSessionRef& session, const se::game::N_Attack& pkt);
bool Handle_N_ThrowGrenade(PacketSessionRef& session, const se::game::N_ThrowGrenade& pkt);
bool Handle_N_Reload(PacketSessionRef& session, const se::game::N_Reload& pkt);
bool Handle_N_WeaponChanged(PacketSessionRef& session, const se::game::N_WeaponChanged& pkt);
bool Handle_N_UseAbility(PacketSessionRef& session, const se::game::N_UseAbility& pkt);
bool Handle_N_KillPlayer(PacketSessionRef& session, const se::game::N_KillPlayer& pkt);
bool Handle_S_ReloadRes(PacketSessionRef& session, const se::game::S_ReloadRes& pkt);
bool Handle_N_EntityHit(PacketSessionRef& session, const se::game::N_EntityHit& pkt);
bool Handle_N_WeaponStatChanged(PacketSessionRef& session, const se::game::N_WeaponStatChanged& pkt);
bool Handle_N_UseItem(PacketSessionRef& session, const se::game::N_UseItem& pkt);
bool Handle_N_PickupItem(PacketSessionRef& session, const se::game::N_PickupItem& pkt);
bool Handle_S_UseStoreRes(PacketSessionRef& session, const se::game::S_UseStoreRes& pkt);
bool Handle_N_ItemGained(PacketSessionRef& session, const se::game::N_ItemGained& pkt);
bool Handle_S_UseItemRes(PacketSessionRef& session, const se::game::S_UseItemRes& pkt);
bool Handle_S_SetSavePointRes(PacketSessionRef& session, const se::game::S_SetSavePointRes& pkt);
bool Handle_N_ChestInteracted(PacketSessionRef& session, const se::game::N_ChestInteracted& pkt);
bool Handle_N_ItemLost(PacketSessionRef& session, const se::game::N_ItemLost& pkt);
bool Handle_N_EquipItem(PacketSessionRef& session, const se::game::N_EquipItem& pkt);
bool Handle_S_EquipItemRes(PacketSessionRef& session, const se::game::S_EquipItemRes& pkt);
bool Handle_N_HealthChanged(PacketSessionRef& session, const se::game::N_HealthChanged& pkt);
bool Handle_N_EntityDied(PacketSessionRef& session, const se::game::N_EntityDied& pkt);
bool Handle_N_EntityRespawned(PacketSessionRef& session, const se::game::N_EntityRespawned& pkt);
bool Handle_N_EntityDestroyed(PacketSessionRef& session, const se::game::N_EntityDestroyed& pkt);
bool Handle_N_TimePointChanged(PacketSessionRef& session, const se::game::N_TimePointChanged& pkt);
bool Handle_N_MaxHealthChanged(PacketSessionRef& session, const se::game::N_MaxHealthChanged& pkt);
bool Handle_N_TimeStormChange(PacketSessionRef& session, const se::game::N_TimeStormChange& pkt);

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
        GPacketHandler[PKT_S_SetNicknameRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_SetNicknameRes>(Handle_S_SetNicknameRes, session, buffer, len); };
        GPacketHandler[PKT_S_MatchQueueEnterRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_MatchQueueEnterRes>(Handle_S_MatchQueueEnterRes, session, buffer, len); };
        GPacketHandler[PKT_S_MatchQueueCancelRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::S_MatchQueueCancelRes>(Handle_S_MatchQueueCancelRes, session, buffer, len); };
        GPacketHandler[PKT_N_MatchFound] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::lobby::N_MatchFound>(Handle_N_MatchFound, session, buffer, len); };
        GPacketHandler[PKT_S_RoomEnterRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::S_RoomEnterRes>(Handle_S_RoomEnterRes, session, buffer, len); };
        GPacketHandler[PKT_S_RoomLeaveRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::S_RoomLeaveRes>(Handle_S_RoomLeaveRes, session, buffer, len); };
        GPacketHandler[PKT_N_EntitySpawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_EntitySpawn>(Handle_N_EntitySpawn, session, buffer, len); };
        GPacketHandler[PKT_N_EntityDespawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_EntityDespawn>(Handle_N_EntityDespawn, session, buffer, len); };
        GPacketHandler[PKT_S_RoomSetupEnd] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::S_RoomSetupEnd>(Handle_S_RoomSetupEnd, session, buffer, len); };
        GPacketHandler[PKT_N_EntitiesSpawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_EntitiesSpawn>(Handle_N_EntitiesSpawn, session, buffer, len); };
        GPacketHandler[PKT_N_RoomClosed] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::room::N_RoomClosed>(Handle_N_RoomClosed, session, buffer, len); };
        GPacketHandler[PKT_N_GameStart] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_GameStart>(Handle_N_GameStart, session, buffer, len); };
        GPacketHandler[PKT_N_GameEnd] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_GameEnd>(Handle_N_GameEnd, session, buffer, len); };
        GPacketHandler[PKT_N_PlayerInitSetup] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_PlayerInitSetup>(Handle_N_PlayerInitSetup, session, buffer, len); };
        GPacketHandler[PKT_N_Move] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Move>(Handle_N_Move, session, buffer, len); };
        GPacketHandler[PKT_N_Jump] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Jump>(Handle_N_Jump, session, buffer, len); };
        GPacketHandler[PKT_N_JumpLand] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_JumpLand>(Handle_N_JumpLand, session, buffer, len); };
        GPacketHandler[PKT_N_DoubleJump] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_DoubleJump>(Handle_N_DoubleJump, session, buffer, len); };
        GPacketHandler[PKT_N_Crouch] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Crouch>(Handle_N_Crouch, session, buffer, len); };
        GPacketHandler[PKT_N_WireAction] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_WireAction>(Handle_N_WireAction, session, buffer, len); };
        GPacketHandler[PKT_N_WireActionEnd] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_WireActionEnd>(Handle_N_WireActionEnd, session, buffer, len); };
        GPacketHandler[PKT_N_WireLaunch] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_WireLaunch>(Handle_N_WireLaunch, session, buffer, len); };
        GPacketHandler[PKT_N_Aim] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Aim>(Handle_N_Aim, session, buffer, len); };
        GPacketHandler[PKT_N_Fire] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Fire>(Handle_N_Fire, session, buffer, len); };
        GPacketHandler[PKT_N_Attack] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Attack>(Handle_N_Attack, session, buffer, len); };
        GPacketHandler[PKT_N_ThrowGrenade] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_ThrowGrenade>(Handle_N_ThrowGrenade, session, buffer, len); };
        GPacketHandler[PKT_N_Reload] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_Reload>(Handle_N_Reload, session, buffer, len); };
        GPacketHandler[PKT_N_WeaponChanged] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_WeaponChanged>(Handle_N_WeaponChanged, session, buffer, len); };
        GPacketHandler[PKT_N_UseAbility] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_UseAbility>(Handle_N_UseAbility, session, buffer, len); };
        GPacketHandler[PKT_N_KillPlayer] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_KillPlayer>(Handle_N_KillPlayer, session, buffer, len); };
        GPacketHandler[PKT_S_ReloadRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::S_ReloadRes>(Handle_S_ReloadRes, session, buffer, len); };
        GPacketHandler[PKT_N_EntityHit] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_EntityHit>(Handle_N_EntityHit, session, buffer, len); };
        GPacketHandler[PKT_N_WeaponStatChanged] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_WeaponStatChanged>(Handle_N_WeaponStatChanged, session, buffer, len); };
        GPacketHandler[PKT_N_UseItem] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_UseItem>(Handle_N_UseItem, session, buffer, len); };
        GPacketHandler[PKT_N_PickupItem] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_PickupItem>(Handle_N_PickupItem, session, buffer, len); };
        GPacketHandler[PKT_S_UseStoreRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::S_UseStoreRes>(Handle_S_UseStoreRes, session, buffer, len); };
        GPacketHandler[PKT_N_ItemGained] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_ItemGained>(Handle_N_ItemGained, session, buffer, len); };
        GPacketHandler[PKT_S_UseItemRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::S_UseItemRes>(Handle_S_UseItemRes, session, buffer, len); };
        GPacketHandler[PKT_S_SetSavePointRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::S_SetSavePointRes>(Handle_S_SetSavePointRes, session, buffer, len); };
        GPacketHandler[PKT_N_ChestInteracted] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_ChestInteracted>(Handle_N_ChestInteracted, session, buffer, len); };
        GPacketHandler[PKT_N_ItemLost] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_ItemLost>(Handle_N_ItemLost, session, buffer, len); };
        GPacketHandler[PKT_N_EquipItem] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_EquipItem>(Handle_N_EquipItem, session, buffer, len); };
        GPacketHandler[PKT_S_EquipItemRes] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::S_EquipItemRes>(Handle_S_EquipItemRes, session, buffer, len); };
        GPacketHandler[PKT_N_HealthChanged] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_HealthChanged>(Handle_N_HealthChanged, session, buffer, len); };
        GPacketHandler[PKT_N_EntityDied] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_EntityDied>(Handle_N_EntityDied, session, buffer, len); };
        GPacketHandler[PKT_N_EntityRespawned] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_EntityRespawned>(Handle_N_EntityRespawned, session, buffer, len); };
        GPacketHandler[PKT_N_EntityDestroyed] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_EntityDestroyed>(Handle_N_EntityDestroyed, session, buffer, len); };
        GPacketHandler[PKT_N_TimePointChanged] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_TimePointChanged>(Handle_N_TimePointChanged, session, buffer, len); };
        GPacketHandler[PKT_N_MaxHealthChanged] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_MaxHealthChanged>(Handle_N_MaxHealthChanged, session, buffer, len); };
        GPacketHandler[PKT_N_TimeStormChange] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::N_TimeStormChange>(Handle_N_TimeStormChange, session, buffer, len); };
    }
    
    static SendBufferRef MakeSendBuffer(se::auth::C_HandshakeReq& pkt) { return MakeSendBuffer(pkt, PKT_C_HandshakeReq); }
    static SendBufferRef MakeSendBuffer(se::auth::C_LoginReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LoginReq); }
    static SendBufferRef MakeSendBuffer(se::auth::C_Ping& pkt) { return MakeSendBuffer(pkt, PKT_C_Ping); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_SetNicknameReq& pkt) { return MakeSendBuffer(pkt, PKT_C_SetNicknameReq); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_MatchQueueEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueEnterReq); }
    static SendBufferRef MakeSendBuffer(se::lobby::C_MatchQueueCancelReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MatchQueueCancelReq); }
    static SendBufferRef MakeSendBuffer(se::room::C_RoomEnterReq& pkt) { return MakeSendBuffer(pkt, PKT_C_RoomEnterReq); }
    static SendBufferRef MakeSendBuffer(se::room::C_RoomLeaveReq& pkt) { return MakeSendBuffer(pkt, PKT_C_RoomLeaveReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_LoadingCompleteReq& pkt) { return MakeSendBuffer(pkt, PKT_C_LoadingCompleteReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_MoveReq& pkt) { return MakeSendBuffer(pkt, PKT_C_MoveReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_JumpReq& pkt) { return MakeSendBuffer(pkt, PKT_C_JumpReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_JumpLand& pkt) { return MakeSendBuffer(pkt, PKT_C_JumpLand); }
    static SendBufferRef MakeSendBuffer(se::game::C_DoubleJumpReq& pkt) { return MakeSendBuffer(pkt, PKT_C_DoubleJumpReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_CrouchReq& pkt) { return MakeSendBuffer(pkt, PKT_C_CrouchReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_WireActionReq& pkt) { return MakeSendBuffer(pkt, PKT_C_WireActionReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_WireActionEnd& pkt) { return MakeSendBuffer(pkt, PKT_C_WireActionEnd); }
    static SendBufferRef MakeSendBuffer(se::game::C_WireLaunchReq& pkt) { return MakeSendBuffer(pkt, PKT_C_WireLaunchReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_AimReq& pkt) { return MakeSendBuffer(pkt, PKT_C_AimReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_FireReq& pkt) { return MakeSendBuffer(pkt, PKT_C_FireReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_ThrowGrenadeReq& pkt) { return MakeSendBuffer(pkt, PKT_C_ThrowGrenadeReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_ReloadReq& pkt) { return MakeSendBuffer(pkt, PKT_C_ReloadReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_WeaponChangeReq& pkt) { return MakeSendBuffer(pkt, PKT_C_WeaponChangeReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_UseAbilityReq& pkt) { return MakeSendBuffer(pkt, PKT_C_UseAbilityReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_UseItemReq& pkt) { return MakeSendBuffer(pkt, PKT_C_UseItemReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_ChestInteractReq& pkt) { return MakeSendBuffer(pkt, PKT_C_ChestInteractReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_PickupItemReq& pkt) { return MakeSendBuffer(pkt, PKT_C_PickupItemReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_UseStoreReq& pkt) { return MakeSendBuffer(pkt, PKT_C_UseStoreReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_SetSavePointReq& pkt) { return MakeSendBuffer(pkt, PKT_C_SetSavePointReq); }
    static SendBufferRef MakeSendBuffer(se::game::C_EquipItemReq& pkt) { return MakeSendBuffer(pkt, PKT_C_EquipItemReq); }

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