#pragma once

#define MAX_CHAT_LEN	256

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40


enum HeroType
{
	UNIT_NONE,

	UNIT_MAGICIAN,
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

	PKT_CS_CHAT = 91,
	PKT_SC_CHAT = 92,

	PKT_MAX = 1024
};

enum SkillKey
{
	KEY_NONE = 0,

	KEY_Q = 1,
	KEY_W = 2,
	KEY_E = 3,
	KEY_R = 4,
};

#pragma pack(push, 1)


struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
	short mSize;
	short mType;
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
	int	mPlayerId;
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
	int		mPlayerId;
	char	mName[MAX_NAME_LEN];

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
	int		mPlayerId;
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
	int		mPlayerId;
	int		mRoomId;
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
	int		mPlayerId;
	int		mRoomId;
	bool	mIsIn;
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
	int		mPlayerId;
	int		mRoomId;
	bool	mIsIn;
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
	}
	int		mPlayerId;
};
struct GameRunNotify : public PacketHeader
{
	GameRunNotify()
	{
		mSize = sizeof(GameRunNotify);
		mType = PKT_SC_ALL_READY;
		mPlayerId = -1;
	}
	int		mPlayerId;
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
		mUnitType = UNIT_NONE;
		mPosX = 0;
		mPosY = 0;
	}
	int			mPlayerId;
	int			mUnitId;
	HeroType	mUnitType;
	float		mPosX;
	float		mPosY;
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
	int		mPlayerId;
};
struct ClientRunCompleteNotify : public PacketHeader
{
	ClientRunCompleteNotify()
	{
		mSize = sizeof(ClientRunCompleteNotify);
		mType = PKT_CS_RUN_COMPLETE;
		mPlayerId = -1;
	}
	int		mPlayerId;
};

struct StartGameNotify : public PacketHeader
{
	StartGameNotify()
	{
		mSize = sizeof(StartGameNotify);
		mType = PKT_SC_START_GAME;
		mPlayerId = -1;
	}
	int		mPlayerId;
};



struct OutGameRequest : public PacketHeader
{
	OutGameRequest()
	{
		mSize = sizeof(OutGameRequest);
		mType = PKT_CS_OUT_GAME;
		mPlayerId = -1;
	}
	int		mPlayerId;
};
struct OutGameResult : public PacketHeader
{
	OutGameResult()
	{
		mSize = sizeof(OutGameResult);
		mType = PKT_SC_OUT_GAME;
		mPlayerId = -1;
	}
	int		mPlayerId;
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
		mCurrentPosX = 0;
		mCurrentPosY = 0;
		mTargetPosX = 0;
		mTargetPosY = 0;

	}
	int		mPlayerId;
	float	mCurrentPosX;
	float	mCurrentPosY;
	float	mTargetPosX;
	float	mTargetPosY;

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
		mUnitType = UNIT_NONE;
		mCurrentPosX = 0;
		mCurrentPosY = 0;
		mTargetPosX = 0;
		mTargetPosY = 0;

	}
	int			mPlayerId;
	int			mUnitId;
	HeroType	mUnitType;
	bool		mIsMove;
	float		mCurrentPosX;
	float		mCurrentPosY;
	float		mTargetPosX;
	float		mTargetPosY;

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
		mCurrentPosX = 0;
		mCurrentPosY = 0;
		mExpectPosX = 0;
		mExpectPosY = 0;
	}
	int			mPlayerId;
	int			mUnitId;
	bool		mIsCrashed;
	float		mCurrentPosX;
	float		mCurrentPosY;
	float		mExpectPosX;
	float		mExpectPosY;

};

struct SkillRequest : public PacketHeader
{
	SkillRequest()
	{
		mSize = sizeof(SkillRequest);
		mType = PKT_CS_SKILL;
		mPlayerId = -1;
		mKey = KEY_NONE;
		mCurrentPosX = 0;
		mCurrentPosY = 0;
		mTargetPosX = 0;
		mTargetPosY = 0;

	}
	int			mPlayerId;
	SkillKey	mKey;
	float		mCurrentPosX;
	float		mCurrentPosY;
	float		mTargetPosX;
	float		mTargetPosY;

};

struct SkillBroadcastResult : public PacketHeader
{
	SkillBroadcastResult()
	{
		mSize = sizeof(SkillBroadcastResult);
		mType = PKT_SC_MOVE;
		mPlayerId = -1;
		mUnitId = -1;
		mKey = KEY_NONE;
		mCurrentPosX = 0;
		mCurrentPosY = 0;
		mTargetPosX = 0;
		mTargetPosY = 0;

	}
	int			mPlayerId;
	int			mUnitId;
	SkillKey	mKey;
	float		mCurrentPosX;
	float		mCurrentPosY;
	float		mTargetPosX;
	float		mTargetPosY;

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
	int	mPlayerId;
	char mChat[MAX_CHAT_LEN];
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
	int	mPlayerId;
	char mName[MAX_NAME_LEN];
	char mChat[MAX_CHAT_LEN];
};



#pragma pack(pop)