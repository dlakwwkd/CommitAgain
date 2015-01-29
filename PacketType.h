#pragma once

#define MAX_NAME_LEN        15
#define MAX_ROOM_NUM        256
#define MAX_COMMENT_LEN	    40
#define MAX_OBSTRUCT_SIZE   100

enum Team
{
    TEAM_N,
    TEAM_C,
    TEAM_1,
    TEAM_2,
    TEAM_3,
    TEAM_4,
    TEAM_5,
    TEAM_6,
    TEAM_7,
    TEAM_8,
};
enum UnitType
{
    UNIT_NONE,
    UNIT_HERO,
    UNIT_MISSILE,
    UNIT_OBSTRUCT,
    UNIT_MOB,
    UNIT_ITEM,
};
enum HeroType
{
    HERO_NONE,
    HERO_MAGICIAN,
    HERO_JUPITER,
    HERO_LAPHINX,
};
enum RoomType
{
    ROOM_NONE,
    ROOM_MELEE,
    ROOM_TEAM,
};
enum EffectType
{
    EF_NONE,
    EF_FIRE,
    EF_ICE,
    EF_SPARK,
    EF_LIGHTNING,
    EF_HIDE,
    EF_ROCK,
    EF_TELEPORT,

    EF_SWIPE,
    EF_METEOR,
    EF_UNHIDE,
};
enum MissileType
{
    MS_NONE,
    MS_FIRE_BALL,
    MS_ICE_BALL,
    MS_SPARK
};
enum ObstructType
{
    OS_NONE,
    OS_ROCK,
    OS_MOVE_ROCK,
    OS_LAVA
};
enum MobType
{
    MOB_NONE,
    MOB_PEA,
};
enum ItemType
{
    ITEM_NONE,
    ITEM_NORMAL,
};
enum BuffTarget
{
    BUFF_NONE,
    BUFF_HP,
    BUFF_SPEED,
    BUFF_DAMAGE,
    BUFF_COOLTIME,
    BUFF_SHIELD,
};

enum SkillKey
{
    SKILL_NONE,

    SKILL_Q = 137,
    SKILL_W = 143,
    SKILL_E = 125,
    SKILL_R = 138,

    SKILL_MAX_NUM = 5,
};

enum PacketTypes
{
    PKT_NONE            = 0,

    PKT_CS_LOGIN        = 1,
    PKT_SC_LOGIN        = 2,

    PKT_CS_MAKE_ROOM    = 11,
    PKT_SC_MAKE_ROOM    = 12,
    PKT_CS_INOUT_ROOM   = 13,
    PKT_SC_INOUT_ROOM   = 14,
    PKT_CS_GAME_READY   = 15,
    PKT_SC_GAME_READY   = 16,
    PKT_SC_ALL_READY    = 17,
    PKT_CS_LOADING_OK   = 18,

    ///////////////
    // SC로만 로딩 정보 전달(맵, 유닛 등) 
    PKT_SC_CREATE_MAP   = 21,
    PKT_SC_CREATE_HERO  = 22,
    PKT_SC_CREATE_MOB   = 23,
    PKT_SC_CREATE_ITEM  = 24,
    ///////////////

    PKT_SC_RUN_COMPLETE = 31,
    PKT_CS_RUN_COMPLETE = 32,

    PKT_SC_START_GAME   = 33,

    PKT_CS_OUT_GAME     = 34,
    PKT_SC_OUT_GAME     = 35,


    PKT_CS_MOVE         = 41,
    PKT_SC_MOVE         = 42,
    PKT_SC_CRASH        = 44,
    PKT_SC_SYNC         = 45,

    PKT_CS_SKILL        = 45,
    PKT_SC_SKILL        = 46,
    PKT_CS_SPLASH       = 47,
    PKT_SC_SPLASH       = 48,

    PKT_SC_MISSILE      = 50,
    PKT_SC_TELEPORT     = 52,
    PKT_SC_HP           = 54,
    PKT_SC_HIDE       = 55,
    PKT_SC_EFFECT       = 56,
    PKT_SC_BUFF         = 57,

    PKT_SC_GAMEOVER     = 100,

    PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
    PacketHeader() : mSize(0), mType(PKT_NONE){}
    short mSize;
    short mType;
};

struct Coord
{
    float x;
    float y;
};

struct RoomInfo
{
    RoomInfo()
    {
        mRoomType = ROOM_NONE;
        mRoomNum = -1;
        mCurPlayerNum = 0;
        mMaxPlayerNum = 0;
        mReadyNum = 0;
        mIsAllReady = false;
    }

    RoomType        mRoomType;
    int             mRoomNum;
    unsigned int    mCurPlayerNum;
    unsigned int    mMaxPlayerNum;
    unsigned int    mReadyNum;
    bool            mIsAllReady;
};

///////////////////////////////////////////////////////////////////////////
/*
    로그인 관련
    */
///////////////////////////////////////////////////////////////////////////
struct LoginRequest : public PacketHeader
{
    LoginRequest()
    {
        mSize = sizeof(LoginRequest);
        mType = PKT_CS_LOGIN;
        ZeroMemory(mPlayerName, MAX_NAME_LEN);
    }
    char    mPlayerName[MAX_NAME_LEN];
};
struct LoginResult : public PacketHeader
{
    LoginResult()
    {
        mSize = sizeof(LoginResult);
        mType = PKT_SC_LOGIN;
        mPlayerId = -1;
        ZeroMemory(mRoomList, MAX_ROOM_NUM);
    }
    int         mPlayerId;
    RoomInfo    mRoomList[MAX_ROOM_NUM];

};


///////////////////////////////////////////////////////////////////////////
/*
    게임 대기방 관련
    */
///////////////////////////////////////////////////////////////////////////
struct MakeRoomRequest : public PacketHeader
{
    MakeRoomRequest()
    {
        mSize = sizeof(MakeRoomRequest);
        mType = PKT_CS_MAKE_ROOM;
        mPlayerId = -1;
    }
    int         mPlayerId;
    RoomInfo    mRoomInfo;
};
struct MakeRoomResult : public PacketHeader
{
    MakeRoomResult()
    {
        mSize = sizeof(MakeRoomResult);
        mType = PKT_SC_MAKE_ROOM;
        mPlayerId = -1;
    }
    int         mPlayerId;
    RoomInfo    mRoomInfo;
};


struct InOutRoomRequest : public PacketHeader
{
    InOutRoomRequest()
    {
        mSize = sizeof(InOutRoomRequest);
        mType = PKT_CS_INOUT_ROOM;
        mPlayerId = -1;
        mIsIn = true;
    }
    int         mPlayerId;
    bool        mIsIn;
    RoomInfo    mRoomInfo;
};
struct InOutRoomResult : public PacketHeader
{
    InOutRoomResult()
    {
        mSize = sizeof(InOutRoomResult);
        mType = PKT_SC_INOUT_ROOM;
        mPlayerId = -1;
        mIsIn = true;
    }
    int         mPlayerId;
    bool        mIsIn;
    RoomInfo    mRoomInfo;
};



///////////////////////////////////////////////////////////////////////////
/*
    게임 로딩, 구동 관련
    */
///////////////////////////////////////////////////////////////////////////
struct GameReadyRequest : public PacketHeader
{
    GameReadyRequest()
    {
        mSize = sizeof(GameReadyRequest);
        mType = PKT_CS_GAME_READY;
        mPlayerId = -1;
        mRoomId = -1;
        mTeam = TEAM_N;
        mHeroType = HERO_NONE;
    }
    int         mPlayerId;
    int         mRoomId;
    Team        mTeam;
    HeroType    mHeroType;
};
struct GameReadyResult : public PacketHeader
{
    GameReadyResult()
    {
        mSize = sizeof(GameReadyResult);
        mType = PKT_SC_GAME_READY;
        mPlayerId = -1;
        mRoomId = -1;
        ZeroMemory(mPlayerName, MAX_NAME_LEN);
    }
    char    mPlayerName[MAX_NAME_LEN];
    int     mPlayerId; 
    int     mRoomId;
};
struct AllReadyNotify : public PacketHeader
{
    AllReadyNotify()
    {
        mSize = sizeof(AllReadyNotify);
        mType = PKT_SC_ALL_READY;
        mPlayerId = -1;
    }
    int     mPlayerId;
};
struct LoadingOKNotify : public PacketHeader
{
    LoadingOKNotify()
    {
        mSize = sizeof(LoadingOKNotify);
        mType = PKT_CS_LOADING_OK;
        mPlayerId = -1;
    }
    int     mPlayerId;
};

struct ServerRunCompleteNotify : public PacketHeader
{
    ServerRunCompleteNotify()
    {
        mSize = sizeof(ServerRunCompleteNotify);
        mType = PKT_SC_RUN_COMPLETE;
        mPlayerId = -1;
    }
    int     mPlayerId;
};
struct ClientRunCompleteNotify : public PacketHeader
{
    ClientRunCompleteNotify()
    {
        mSize = sizeof(ClientRunCompleteNotify);
        mType = PKT_CS_RUN_COMPLETE;
        mPlayerId = -1;
    }
    int     mPlayerId;
};

struct StartGameNotify : public PacketHeader
{
    StartGameNotify()
    {
        mSize = sizeof(StartGameNotify);
        mType = PKT_SC_START_GAME;
        mPlayerId = -1;
    }
    int     mPlayerId;
};

struct OutGameRequest : public PacketHeader
{
    OutGameRequest()
    {
        mSize = sizeof(OutGameRequest);
        mType = PKT_CS_OUT_GAME;
        mPlayerId = -1;
    }
    int     mPlayerId;
};
struct OutGameResult : public PacketHeader
{
    OutGameResult()
    {
        mSize = sizeof(OutGameResult);
        mType = PKT_SC_OUT_GAME;
        mPlayerId = -1;
    }
    int     mPlayerId;
};


///////////////////////////////////////////////////////////////////////////
/*
    유닛 생성 관련
*/
///////////////////////////////////////////////////////////////////////////
struct CreateHeroResult : public PacketHeader
{
    CreateHeroResult()
    {
        mSize = sizeof(CreateHeroResult);
        mType = PKT_SC_CREATE_HERO;
        mPlayerId = -1;
        mUnitId = -1;
        mPos = { 0, };
        mTeam = TEAM_N;
        mRoomType = ROOM_NONE;
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mPos;
    Team        mTeam;
    RoomType    mRoomType;
};

struct CreateMapResult : public PacketHeader
{
    CreateMapResult()
    {
        mSize = sizeof(CreateMapResult);
        mType = PKT_SC_CREATE_MAP;
        mPlayerId = -1;
        mUnitId = -1;
        mPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mPos;
};

struct CreateMobResult : public PacketHeader
{
    CreateMobResult()
    {
        mSize = sizeof(CreateMobResult);
        mType = PKT_SC_CREATE_MOB;
        mPlayerId = -1;
        mUnitId = -1;
        mHp = 0;
        mSpeed = 0;
        mPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    int         mHp;
    float       mSpeed;
    Coord       mPos;
};

struct ItemBroadcastResult : public PacketHeader
{
    ItemBroadcastResult()
    {
        mSize = sizeof(ItemBroadcastResult);
        mType = PKT_SC_CREATE_ITEM;
        mPlayerId = -1;
        mUnitId = -1;
        mIsCreate = false;
        mPos = { 0, };
        mBuffType = BUFF_NONE;
    }
    int         mPlayerId;
    int         mUnitId;
    bool        mIsCreate;
    Coord       mPos;
    BuffTarget  mBuffType;
};


///////////////////////////////////////////////////////////////////////////
/*
    게임 플레이 관련
    */
///////////////////////////////////////////////////////////////////////////
struct MoveRequest : public PacketHeader
{
    MoveRequest()
    {
        mSize = sizeof(MoveRequest);
        mType = PKT_CS_MOVE;
        mPlayerId = -1;
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    Coord       mTargetPos;
};

struct MoveBroadcastResult : public PacketHeader
{
    MoveBroadcastResult()
    {
        mSize = sizeof(MoveBroadcastResult);
        mType = PKT_SC_MOVE;
        mPlayerId = -1;
        mUnitId = -1;
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mTargetPos;
};

struct CrashedBroadcastResult : public PacketHeader
{
    CrashedBroadcastResult()
    {
        mSize = sizeof(CrashedBroadcastResult);
        mType = PKT_SC_CRASH;
        mPlayerId = -1;
        mUnitId = -1;
        mCurrentPos = { 0, };
        mExpectPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mCurrentPos;
    Coord       mExpectPos;
};

struct SyncPosBroadcastResult : public PacketHeader
{
    SyncPosBroadcastResult()
    {
        mSize = sizeof(SyncPosBroadcastResult);
        mType = PKT_SC_SYNC;
        mPlayerId = -1;
        mUnitId = -1;
        mCurrentPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mCurrentPos;
};

struct SkillRequest : public PacketHeader
{
    SkillRequest()
    {
        mSize = sizeof(SkillRequest);
        mType = PKT_CS_SKILL;
        mPlayerId = -1;
        mKey = SKILL_NONE;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    SkillKey    mKey;
    Coord       mCurrentPos;
    Coord       mTargetPos;
};

struct SkillBroadcastResult : public PacketHeader
{
    SkillBroadcastResult()
    {
        mSize = sizeof(SkillBroadcastResult);
        mType = PKT_SC_SKILL;
        mPlayerId = -1;
        mUnitId = -1;
        mKey = SKILL_NONE;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    SkillKey    mKey;
    Coord       mCurrentPos;
    Coord       mTargetPos;
};

struct SplashSkillRequest : public PacketHeader
{
    SplashSkillRequest()
    {
        mSize = sizeof(SplashSkillRequest);
        mType = PKT_CS_SPLASH;
        mPlayerId = -1;
        mKey = SKILL_NONE;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int			mPlayerId;
    SkillKey	mKey;
    Coord   	mCurrentPos;
    Coord   	mTargetPos;
};

struct SplashSkillBroadcastResult : public PacketHeader
{
    SplashSkillBroadcastResult()
    {
        mSize = sizeof(SplashSkillBroadcastResult);
        mType = PKT_SC_SPLASH;
        mPlayerId = -1;
        mUnitId = -1;
        mKey = SKILL_NONE;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int			mPlayerId;
    int			mUnitId;
    SkillKey	mKey;
    Coord   	mCurrentPos;
    Coord   	mTargetPos;
};

struct MissileBroadcastResult : public PacketHeader
{
    MissileBroadcastResult()
    {
        mSize = sizeof(MissileBroadcastResult);
        mType = PKT_SC_MISSILE;
        mPlayerId = -1;
        mUnitId = -1;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mCurrentPos;
    Coord       mTargetPos;
};

struct TeleportBroadcastResult : public PacketHeader
{
    TeleportBroadcastResult()
    {
        mSize = sizeof(TeleportBroadcastResult);
        mType = PKT_SC_TELEPORT;
        mPlayerId = -1;
        mUnitId = -1;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mCurrentPos;
    Coord       mTargetPos;
};
struct HideBroadcastResult : public PacketHeader
{
    HideBroadcastResult()
    {
        mSize = sizeof(HideBroadcastResult);
        mType = PKT_SC_HIDE;
        mPlayerId = -1;
        mUnitId = -1;
        mIsOn = false;
    }
    int         mPlayerId;
    int         mUnitId;
    bool        mIsOn;
};
struct EffectBroadcastResult : public PacketHeader
{
    EffectBroadcastResult()
    {
        mSize = sizeof(EffectBroadcastResult);
        mType = PKT_SC_EFFECT;
        mPlayerId = -1;
        mEffectType = EF_NONE;
        mPos = { 0, };
    }
    int         mPlayerId;
    EffectType  mEffectType;
    Coord       mPos;
};
struct HpBroadcastResult : public PacketHeader
{
    HpBroadcastResult()
    {
        mSize = sizeof(HpBroadcastResult);
        mType = PKT_SC_HP;
        mUnitId = -1;
        mHp = 0;
    }
    int         mPlayerId;
    int         mUnitId;
    int         mHp;
};
struct BuffBroadcastResult : public PacketHeader
{
    BuffBroadcastResult()
    {
        mSize = sizeof(BuffBroadcastResult);
        mType = PKT_SC_BUFF;
        mUnitId = -1;
        mBonus = 0;
        mBuffTarget = BUFF_NONE;
        mIsOn = false;
    }
    int         mPlayerId;
    int         mUnitId;
    float       mBonus;
    BuffTarget  mBuffTarget;
    bool        mIsOn;
};


///////////////////////////////////////////////////////////////////////////
/*
    게임 오버
*/
///////////////////////////////////////////////////////////////////////////
struct GameOverNotify : public PacketHeader
{
    GameOverNotify()
    {
        mSize = sizeof(GameOverNotify);
        mType = PKT_SC_GAMEOVER;
        mPlayerId = -1;
        mWinTeam = TEAM_N;
    }
    int         mPlayerId;
    Team        mWinTeam;
};



#pragma pack(pop)