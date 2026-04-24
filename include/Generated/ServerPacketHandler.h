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
    PKT_N_EntitiesSpawn = 3101,
    PKT_N_EntityDespawn = 3102,
    PKT_S_RoomSetupEnd = 3103,
    PKT_N_RoomClosed = 3200,
    PKT_C_LoadingCompleteReq = 4000,
    PKT_N_GameStart = 4001,
    PKT_N_GameEnd = 4002,
    PKT_N_PlayerInitSetup = 4003,
    PKT_C_MoveReq = 4010,
    PKT_N_Move = 4011,
    PKT_C_JumpReq = 4020,
    PKT_N_Jump = 4021,
    PKT_C_DoubleJumpReq = 4022,
    PKT_N_DoubleJump = 4023,
    PKT_C_JumpLand = 4024,
    PKT_N_JumpLand = 4025,
    PKT_C_CrouchReq = 4030,
    PKT_N_Crouch = 4031,
    PKT_C_WireLaunchReq = 4040,
    PKT_N_WireLaunch = 4041,
    PKT_C_WireActionReq = 4042,
    PKT_N_WireAction = 4043,
    PKT_C_WireActionEnd = 4044,
    PKT_N_WireActionEnd = 4045,
    PKT_C_AimReq = 4090,
    PKT_N_Aim = 4091,
    PKT_C_FireReq = 4100,
    PKT_N_Fire = 4101,
    PKT_N_Attack = 4103,
    PKT_C_ThrowGrenadeReq = 4104,
    PKT_N_ThrowGrenade = 4105,
    PKT_C_ReloadReq = 4106,
    PKT_S_ReloadRes = 4107,
    PKT_N_Reload = 4108,
    PKT_C_WeaponChangeReq = 4109,
    PKT_N_WeaponChanged = 4110,
    PKT_N_WeaponStatChanged = 4115,
    PKT_N_WeaponStatSnapshot = 4116,
    PKT_C_UseAbilityReq = 4120,
    PKT_N_UseAbility = 4121,
    PKT_N_EntityHit = 4150,
    PKT_N_KillPlayer = 4190,
    PKT_C_UseItemReq = 4200,
    PKT_S_UseItemRes = 4201,
    PKT_N_UseItem = 4202,
    PKT_C_ChestInteractReq = 4210,
    PKT_N_ChestInteracted = 4211,
    PKT_C_PickupItemReq = 4220,
    PKT_N_PickupItem = 4221,
    PKT_C_EquipItemReq = 4230,
    PKT_S_EquipItemRes = 4231,
    PKT_N_EquipItem = 4232,
    PKT_C_UseStoreReq = 4240,
    PKT_S_UseStoreRes = 4241,
    PKT_N_ItemGained = 4250,
    PKT_N_ItemLost = 4251,
    PKT_N_ItemSnapshot = 4252,
    PKT_C_SetSavePointReq = 4290,
    PKT_S_SetSavePointRes = 4291,
    PKT_N_HealthChanged = 4300,
    PKT_N_MaxHealthChanged = 4301,
    PKT_N_HealthSnapshot = 4302,
    PKT_N_TimePointChanged = 4310,
    PKT_N_TimePointSnapshot = 4311,
    PKT_N_SkillUnlock = 4320,
    PKT_C_SkillEquipReq = 4321,
    PKT_S_SkillEquipRes = 4322,
    PKT_N_SkillUnlockSnapshot = 4323,
    PKT_N_EntityDied = 4390,
    PKT_N_EntityRespawned = 4391,
    PKT_N_EntityDestroyed = 4392,
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
bool Handle_C_DoubleJumpReq(PacketSessionRef& session, const se::game::C_DoubleJumpReq& pkt);
bool Handle_C_JumpLand(PacketSessionRef& session, const se::game::C_JumpLand& pkt);
bool Handle_C_CrouchReq(PacketSessionRef& session, const se::game::C_CrouchReq& pkt);
bool Handle_C_WireLaunchReq(PacketSessionRef& session, const se::game::C_WireLaunchReq& pkt);
bool Handle_C_WireActionReq(PacketSessionRef& session, const se::game::C_WireActionReq& pkt);
bool Handle_C_WireActionEnd(PacketSessionRef& session, const se::game::C_WireActionEnd& pkt);
bool Handle_C_AimReq(PacketSessionRef& session, const se::game::C_AimReq& pkt);
bool Handle_C_FireReq(PacketSessionRef& session, const se::game::C_FireReq& pkt);
bool Handle_C_ThrowGrenadeReq(PacketSessionRef& session, const se::game::C_ThrowGrenadeReq& pkt);
bool Handle_C_ReloadReq(PacketSessionRef& session, const se::game::C_ReloadReq& pkt);
bool Handle_C_WeaponChangeReq(PacketSessionRef& session, const se::game::C_WeaponChangeReq& pkt);
bool Handle_C_UseAbilityReq(PacketSessionRef& session, const se::game::C_UseAbilityReq& pkt);
bool Handle_C_UseItemReq(PacketSessionRef& session, const se::game::C_UseItemReq& pkt);
bool Handle_C_ChestInteractReq(PacketSessionRef& session, const se::game::C_ChestInteractReq& pkt);
bool Handle_C_PickupItemReq(PacketSessionRef& session, const se::game::C_PickupItemReq& pkt);
bool Handle_C_EquipItemReq(PacketSessionRef& session, const se::game::C_EquipItemReq& pkt);
bool Handle_C_UseStoreReq(PacketSessionRef& session, const se::game::C_UseStoreReq& pkt);
bool Handle_C_SetSavePointReq(PacketSessionRef& session, const se::game::C_SetSavePointReq& pkt);
bool Handle_C_SkillEquipReq(PacketSessionRef& session, const se::game::C_SkillEquipReq& pkt);

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
        GPacketHandler[PKT_C_DoubleJumpReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_DoubleJumpReq>(Handle_C_DoubleJumpReq, session, buffer, len); };
        GPacketHandler[PKT_C_JumpLand] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_JumpLand>(Handle_C_JumpLand, session, buffer, len); };
        GPacketHandler[PKT_C_CrouchReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_CrouchReq>(Handle_C_CrouchReq, session, buffer, len); };
        GPacketHandler[PKT_C_WireLaunchReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WireLaunchReq>(Handle_C_WireLaunchReq, session, buffer, len); };
        GPacketHandler[PKT_C_WireActionReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WireActionReq>(Handle_C_WireActionReq, session, buffer, len); };
        GPacketHandler[PKT_C_WireActionEnd] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WireActionEnd>(Handle_C_WireActionEnd, session, buffer, len); };
        GPacketHandler[PKT_C_AimReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_AimReq>(Handle_C_AimReq, session, buffer, len); };
        GPacketHandler[PKT_C_FireReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_FireReq>(Handle_C_FireReq, session, buffer, len); };
        GPacketHandler[PKT_C_ThrowGrenadeReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ThrowGrenadeReq>(Handle_C_ThrowGrenadeReq, session, buffer, len); };
        GPacketHandler[PKT_C_ReloadReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ReloadReq>(Handle_C_ReloadReq, session, buffer, len); };
        GPacketHandler[PKT_C_WeaponChangeReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_WeaponChangeReq>(Handle_C_WeaponChangeReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseAbilityReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseAbilityReq>(Handle_C_UseAbilityReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseItemReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseItemReq>(Handle_C_UseItemReq, session, buffer, len); };
        GPacketHandler[PKT_C_ChestInteractReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_ChestInteractReq>(Handle_C_ChestInteractReq, session, buffer, len); };
        GPacketHandler[PKT_C_PickupItemReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_PickupItemReq>(Handle_C_PickupItemReq, session, buffer, len); };
        GPacketHandler[PKT_C_EquipItemReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_EquipItemReq>(Handle_C_EquipItemReq, session, buffer, len); };
        GPacketHandler[PKT_C_UseStoreReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_UseStoreReq>(Handle_C_UseStoreReq, session, buffer, len); };
        GPacketHandler[PKT_C_SetSavePointReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_SetSavePointReq>(Handle_C_SetSavePointReq, session, buffer, len); };
        GPacketHandler[PKT_C_SkillEquipReq] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<se::game::C_SkillEquipReq>(Handle_C_SkillEquipReq, session, buffer, len); };
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
    static SendBufferRef MakeSendBuffer(se::room::N_EntitiesSpawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntitiesSpawn); }
    static SendBufferRef MakeSendBuffer(se::room::N_EntityDespawn& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDespawn); }
    static SendBufferRef MakeSendBuffer(se::room::S_RoomSetupEnd& pkt) { return MakeSendBuffer(pkt, PKT_S_RoomSetupEnd); }
    static SendBufferRef MakeSendBuffer(se::room::N_RoomClosed& pkt) { return MakeSendBuffer(pkt, PKT_N_RoomClosed); }
    static SendBufferRef MakeSendBuffer(se::game::N_GameStart& pkt) { return MakeSendBuffer(pkt, PKT_N_GameStart); }
    static SendBufferRef MakeSendBuffer(se::game::N_GameEnd& pkt) { return MakeSendBuffer(pkt, PKT_N_GameEnd); }
    static SendBufferRef MakeSendBuffer(se::game::N_PlayerInitSetup& pkt) { return MakeSendBuffer(pkt, PKT_N_PlayerInitSetup); }
    static SendBufferRef MakeSendBuffer(se::game::N_Move& pkt) { return MakeSendBuffer(pkt, PKT_N_Move); }
    static SendBufferRef MakeSendBuffer(se::game::N_Jump& pkt) { return MakeSendBuffer(pkt, PKT_N_Jump); }
    static SendBufferRef MakeSendBuffer(se::game::N_DoubleJump& pkt) { return MakeSendBuffer(pkt, PKT_N_DoubleJump); }
    static SendBufferRef MakeSendBuffer(se::game::N_JumpLand& pkt) { return MakeSendBuffer(pkt, PKT_N_JumpLand); }
    static SendBufferRef MakeSendBuffer(se::game::N_Crouch& pkt) { return MakeSendBuffer(pkt, PKT_N_Crouch); }
    static SendBufferRef MakeSendBuffer(se::game::N_WireLaunch& pkt) { return MakeSendBuffer(pkt, PKT_N_WireLaunch); }
    static SendBufferRef MakeSendBuffer(se::game::N_WireAction& pkt) { return MakeSendBuffer(pkt, PKT_N_WireAction); }
    static SendBufferRef MakeSendBuffer(se::game::N_WireActionEnd& pkt) { return MakeSendBuffer(pkt, PKT_N_WireActionEnd); }
    static SendBufferRef MakeSendBuffer(se::game::N_Aim& pkt) { return MakeSendBuffer(pkt, PKT_N_Aim); }
    static SendBufferRef MakeSendBuffer(se::game::N_Fire& pkt) { return MakeSendBuffer(pkt, PKT_N_Fire); }
    static SendBufferRef MakeSendBuffer(se::game::N_Attack& pkt) { return MakeSendBuffer(pkt, PKT_N_Attack); }
    static SendBufferRef MakeSendBuffer(se::game::N_ThrowGrenade& pkt) { return MakeSendBuffer(pkt, PKT_N_ThrowGrenade); }
    static SendBufferRef MakeSendBuffer(se::game::S_ReloadRes& pkt) { return MakeSendBuffer(pkt, PKT_S_ReloadRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_Reload& pkt) { return MakeSendBuffer(pkt, PKT_N_Reload); }
    static SendBufferRef MakeSendBuffer(se::game::N_WeaponChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_WeaponChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_WeaponStatChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_WeaponStatChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_WeaponStatSnapshot& pkt) { return MakeSendBuffer(pkt, PKT_N_WeaponStatSnapshot); }
    static SendBufferRef MakeSendBuffer(se::game::N_UseAbility& pkt) { return MakeSendBuffer(pkt, PKT_N_UseAbility); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityHit& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityHit); }
    static SendBufferRef MakeSendBuffer(se::game::N_KillPlayer& pkt) { return MakeSendBuffer(pkt, PKT_N_KillPlayer); }
    static SendBufferRef MakeSendBuffer(se::game::S_UseItemRes& pkt) { return MakeSendBuffer(pkt, PKT_S_UseItemRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_UseItem& pkt) { return MakeSendBuffer(pkt, PKT_N_UseItem); }
    static SendBufferRef MakeSendBuffer(se::game::N_ChestInteracted& pkt) { return MakeSendBuffer(pkt, PKT_N_ChestInteracted); }
    static SendBufferRef MakeSendBuffer(se::game::N_PickupItem& pkt) { return MakeSendBuffer(pkt, PKT_N_PickupItem); }
    static SendBufferRef MakeSendBuffer(se::game::S_EquipItemRes& pkt) { return MakeSendBuffer(pkt, PKT_S_EquipItemRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_EquipItem& pkt) { return MakeSendBuffer(pkt, PKT_N_EquipItem); }
    static SendBufferRef MakeSendBuffer(se::game::S_UseStoreRes& pkt) { return MakeSendBuffer(pkt, PKT_S_UseStoreRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_ItemGained& pkt) { return MakeSendBuffer(pkt, PKT_N_ItemGained); }
    static SendBufferRef MakeSendBuffer(se::game::N_ItemLost& pkt) { return MakeSendBuffer(pkt, PKT_N_ItemLost); }
    static SendBufferRef MakeSendBuffer(se::game::N_ItemSnapshot& pkt) { return MakeSendBuffer(pkt, PKT_N_ItemSnapshot); }
    static SendBufferRef MakeSendBuffer(se::game::S_SetSavePointRes& pkt) { return MakeSendBuffer(pkt, PKT_S_SetSavePointRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_HealthChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_HealthChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_MaxHealthChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_MaxHealthChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_HealthSnapshot& pkt) { return MakeSendBuffer(pkt, PKT_N_HealthSnapshot); }
    static SendBufferRef MakeSendBuffer(se::game::N_TimePointChanged& pkt) { return MakeSendBuffer(pkt, PKT_N_TimePointChanged); }
    static SendBufferRef MakeSendBuffer(se::game::N_TimePointSnapshot& pkt) { return MakeSendBuffer(pkt, PKT_N_TimePointSnapshot); }
    static SendBufferRef MakeSendBuffer(se::game::N_SkillUnlock& pkt) { return MakeSendBuffer(pkt, PKT_N_SkillUnlock); }
    static SendBufferRef MakeSendBuffer(se::game::S_SkillEquipRes& pkt) { return MakeSendBuffer(pkt, PKT_S_SkillEquipRes); }
    static SendBufferRef MakeSendBuffer(se::game::N_SkillUnlockSnapshot& pkt) { return MakeSendBuffer(pkt, PKT_N_SkillUnlockSnapshot); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityDied& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDied); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityRespawned& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityRespawned); }
    static SendBufferRef MakeSendBuffer(se::game::N_EntityDestroyed& pkt) { return MakeSendBuffer(pkt, PKT_N_EntityDestroyed); }
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