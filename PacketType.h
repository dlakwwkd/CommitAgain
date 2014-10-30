#pragma once

#define MAX_CHAT_LEN	256

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

enum PacketTypes
{
	PKT_NONE	= 0,
	
	PKT_CS_LOGIN	= 1,
	PKT_SC_LOGIN	= 2,

	PKT_CS_MAKE_ROOM = 11,
	PKT_SC_MAKE_ROOM = 12,
	PKT_CS_INOUT_ROOM = 13,
	PKT_SC_INOUT_ROOM = 14,

	PKT_CS_PLAY_GAME = 21,
	PKT_SC_PLAY_GAME = 22,
	PKT_CS_OUT_GAME = 23,
	PKT_SC_OUT_GAME = 24,

	PKT_CS_CHAT		= 31,
	PKT_SC_CHAT		= 32,

	PKT_CS_CREATE_HERO	= 41,
	PKT_SC_CREATE_HERO	= 42,

	PKT_CS_MOVE = 51,
	PKT_SC_MOVE = 52,


	PKT_MAX	= 1024
} ;
#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
	short mSize ;
	short mType ;
} ;

///////////////////////////////////////////////////////////////////////////
/*
	로그인 관련
*/
///////////////////////////////////////////////////////////////////////////
struct LoginRequest : public PacketHeader
{
	LoginRequest()
	{
		mSize = sizeof(LoginRequest) ;
		mType = PKT_CS_LOGIN ;
		mPlayerId = -1 ;
	}
	int	mPlayerId ;
} ;
struct LoginResult : public PacketHeader
{
	LoginResult()
	{
		mSize = sizeof(LoginResult) ;
		mType = PKT_SC_LOGIN ;
		mPlayerId = -1 ;
		memset(mName, 0, MAX_NAME_LEN) ;
	}
	int		mPlayerId ;
	char	mName[MAX_NAME_LEN] ;

} ;


///////////////////////////////////////////////////////////////////////////
/*
	게임 대기방, 게임 실행 관련
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
	게임 내 유닛 관련
*/
///////////////////////////////////////////////////////////////////////////
struct CreateHeroRequest : public PacketHeader
{
	CreateHeroRequest()
	{
		mSize = sizeof(CreateHeroRequest);
		mType = PKT_CS_CREATE_HERO;
		mPlayerId = -1;
		mUnitId = -1;
		mPosX = 0;
		mPosY = 0;
	}
	int		mPlayerId;
	int		mUnitId;
	float	mPosX;
	float	mPosY;
};
struct CreateHeroResult : public PacketHeader
{
	CreateHeroResult()
	{
		mSize = sizeof(CreateHeroRequest);
		mType = PKT_SC_CREATE_HERO;
		mPlayerId = -1;
		mUnitId = -1;
		mPosX = 0;
		mPosY = 0;
	}
	int		mPlayerId;
	int		mUnitId;
	float	mPosX;
	float	mPosY;
};



struct MoveRequest : public PacketHeader
{
	MoveRequest()
	{
		mSize = sizeof(MoveRequest);
		mType = PKT_CS_MOVE;
		mPlayerId = -1;
		mPosX = 0;
		mPosY = 0;
	}
	int		mPlayerId;
	float	mPosX;
	float	mPosY;
};
struct MoveBroadcastResult : public PacketHeader
{
	MoveBroadcastResult()
	{
		mSize = sizeof(MoveBroadcastResult);
		mType = PKT_SC_MOVE;
		mPlayerId = -1;
		mPosX = 0;
		mPosY = 0;
	}
	int		mPlayerId;
	float	mPosX;
	float	mPosY;
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