#pragma once

#define MAX_CHAT_LEN        256
#define MAX_NAME_LEN        30
#define MAX_COMMENT_LEN	    40
#define MAX_OBSTRUCT_SIZE   100

enum UnitType
{
    UNIT_NONE,
    UNIT_HERO,
    UNIT_MISSILE,
    UNIT_OBSTRUCT,
};
enum HeroType
{
    HERO_NONE,
    HERO_MAGICIAN,
    HERO_JUPITER,
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
    OS_FIRE_BALL,
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
    PKT_NONE = 0,

    PKT_CS_LOGIN = 1,
    PKT_SC_LOGIN = 2,

    PKT_CS_MAKE_ROOM = 11,
    PKT_SC_MAKE_ROOM = 12,
    PKT_CS_INOUT_ROOM = 13,
    PKT_SC_INOUT_ROOM = 14,
    PKT_CS_GAME_READY = 15,
    PKT_SC_ALL_READY = 16,

    ///////////////
    // SC로만 로딩 정보 전달(맵, 유닛 등) 
    PKT_SC_CREATE_MAP = 21,
    PKT_SC_CREATE_HERO = 22,
    ///////////////

    PKT_SC_RUN_COMPLETE = 31,
    PKT_CS_RUN_COMPLETE = 32,

    PKT_SC_START_GAME = 33,

    PKT_CS_OUT_GAME = 34,
    PKT_SC_OUT_GAME = 35,


    PKT_CS_MOVE = 41,
    PKT_SC_MOVE = 42,

    PKT_SC_CRASH = 44,

    PKT_CS_SKILL = 45,
    PKT_SC_SKILL = 46,

    PKT_CS_SPLASH = 47,
    PKT_SC_SPLASH = 48,

    PKT_SC_MISSILE = 50,
    PKT_SC_TELEPORT = 52,
    PKT_SC_HP = 54,

    PKT_CS_CHAT = 91,
    PKT_SC_CHAT = 92,

    PKT_SC_GAMEOVER = 100,

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

struct MapObt
{
    MapObt() : mUnitID(-1), mPos({-1,-1}){}
    MapObt(int unitId, Coord pos) : mUnitID(unitId), mPos(pos){}
    int     mUnitID;
    Coord   mPos;
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
        mPlayerId = -1;
    }
    int     mPlayerId;
};
struct LoginResult : public PacketHeader
{
    LoginResult()
    {
        mSize = sizeof(LoginResult);
        mType = PKT_SC_LOGIN;
        mPlayerId = -1;
        memset(mName, 0, MAX_NAME_LEN);
    }
    int     mPlayerId;
    char    mName[MAX_NAME_LEN];

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
    int     mPlayerId;
};
struct MakeRoomResult : public PacketHeader
{
    MakeRoomResult()
    {
        mSize = sizeof(MakeRoomResult);
        mType = PKT_SC_MAKE_ROOM;
        mPlayerId = -1;
        mRoomId = -1;
    }
    int     mPlayerId;
    int     mRoomId;
};


struct InOutRoomRequest : public PacketHeader
{
    InOutRoomRequest()
    {
        mSize = sizeof(InOutRoomRequest);
        mType = PKT_CS_INOUT_ROOM;
        mPlayerId = -1;
        mRoomId = -1;
        mIsIn = true;
    }
    int     mPlayerId;
    int     mRoomId;
    bool    mIsIn;
};
struct InOutRoomResult : public PacketHeader
{
    InOutRoomResult()
    {
        mSize = sizeof(InOutRoomResult);
        mType = PKT_SC_INOUT_ROOM;
        mPlayerId = -1;
        mRoomId = -1;
        mIsIn = true;
    }
    int     mPlayerId;
    int     mRoomId;
    bool    mIsIn;
};



///////////////////////////////////////////////////////////////////////////
/*
    게임 로딩, 구동 관련
    */
///////////////////////////////////////////////////////////////////////////
struct GameReadyNotify : public PacketHeader
{
    GameReadyNotify()
    {
        mSize = sizeof(GameReadyNotify);
        mType = PKT_CS_GAME_READY;
        mPlayerId = -1;
        mRoomId = -1;
        mHeroType = HERO_NONE;
    }
    int         mPlayerId;
    int         mRoomId;
    HeroType    mHeroType;
};
struct GameRunNotify : public PacketHeader
{
    GameRunNotify()
    {
        mSize = sizeof(GameRunNotify);
        mType = PKT_SC_ALL_READY;
        mPlayerId = -1;
    }
    int         mPlayerId;
};


//////////////////////////////////////////////////////////////////////////
// 로딩 관련 데이터 전송
struct CreateHeroResult : public PacketHeader
{
    CreateHeroResult()
    {
        mSize = sizeof(CreateHeroResult);
        mType = PKT_SC_CREATE_HERO;
        mPlayerId = -1;
        mUnitId = -1;
        mPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    Coord       mPos;
};

struct CreateMapResult : public PacketHeader
{
    CreateMapResult()
    {
        mSize = sizeof(CreateMapResult);
        mType = PKT_SC_CREATE_MAP;
        mPlayerId = -1;
        ZeroMemory(mMapObtList, MAX_OBSTRUCT_SIZE);
    }
    int         mPlayerId;
    MapObt      mMapObtList[MAX_OBSTRUCT_SIZE];
};
//////////////////////////////////////////////////////////////////////////


struct ServerRunCompleteNotify : public PacketHeader
{
    ServerRunCompleteNotify()
    {
        mSize = sizeof(ServerRunCompleteNotify);
        mType = PKT_SC_RUN_COMPLETE;
        mPlayerId = -1;
    }
    int         mPlayerId;
};
struct ClientRunCompleteNotify : public PacketHeader
{
    ClientRunCompleteNotify()
    {
        mSize = sizeof(ClientRunCompleteNotify);
        mType = PKT_CS_RUN_COMPLETE;
        mPlayerId = -1;
    }
    int         mPlayerId;
};

struct StartGameNotify : public PacketHeader
{
    StartGameNotify()
    {
        mSize = sizeof(StartGameNotify);
        mType = PKT_SC_START_GAME;
        mPlayerId = -1;
    }
    int         mPlayerId;
};



struct OutGameRequest : public PacketHeader
{
    OutGameRequest()
    {
        mSize = sizeof(OutGameRequest);
        mType = PKT_CS_OUT_GAME;
        mPlayerId = -1;
    }
    int         mPlayerId;
};
struct OutGameResult : public PacketHeader
{
    OutGameResult()
    {
        mSize = sizeof(OutGameResult);
        mType = PKT_SC_OUT_GAME;
        mPlayerId = -1;
    }
    int         mPlayerId;
};



///////////////////////////////////////////////////////////////////////////
/*
    게임 내 유닛 관련
    */
///////////////////////////////////////////////////////////////////////////
struct MoveRequest : public PacketHeader
{
    MoveRequest()
    {
        mSize = sizeof(MoveRequest);
        mType = PKT_CS_MOVE;
        mPlayerId = -1;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    Coord       mCurrentPos;
    Coord       mTargetPos;
};

struct MoveBroadcastResult : public PacketHeader
{
    MoveBroadcastResult()
    {
        mSize = sizeof(MoveBroadcastResult);
        mType = PKT_SC_MOVE;
        mIsMove = false;
        mPlayerId = -1;
        mUnitId = -1;
        mCurrentPos = { 0, };
        mTargetPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    bool        mIsMove;
    Coord       mCurrentPos;
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
        mIsCrashed = true;
        mCurrentPos = { 0, };
        mExpectPos = { 0, };
    }
    int         mPlayerId;
    int         mUnitId;
    bool        mIsCrashed;
    Coord       mCurrentPos;
    Coord       mExpectPos;
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
///////////////////////////////////////////////////////////////////////////
/*
    채팅 관련
    */
///////////////////////////////////////////////////////////////////////////
struct ChatBroadcastRequest : public PacketHeader
{
    ChatBroadcastRequest()
    {
        mSize = sizeof(ChatBroadcastRequest);
        mType = PKT_CS_CHAT;
        mPlayerId = -1;
        memset(mChat, 0, MAX_CHAT_LEN);
    }
    int         mPlayerId;
    char        mChat[MAX_CHAT_LEN];
};
struct ChatBroadcastResult : public PacketHeader
{
    ChatBroadcastResult()
    {
        mSize = sizeof(ChatBroadcastResult);
        mType = PKT_SC_CHAT;
        mPlayerId = -1;
        memset(mName, 0, MAX_NAME_LEN);
        memset(mChat, 0, MAX_CHAT_LEN);
    }
    int         mPlayerId;
    char        mName[MAX_NAME_LEN];
    char        mChat[MAX_CHAT_LEN];
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
        mLoseId = -1;
    }
    int         mPlayerId;
    int         mLoseId;
};



#pragma pack(pop)