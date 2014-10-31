#include "stdafx.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "GameRoom.h"
//#include "DatabaseJobContext.h"
//#include "DatabaseJobManager.h"

//@{ Handler Helper

typedef void(*HandlerFunc)(ClientSession* session);

static HandlerFunc HandlerTable[PKT_MAX];

static void DefaultHandler(ClientSession* session)
{
	printf("[DEBUG] Invalid packet handler", session->GetPlayerId());
	session->Disconnect();
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for (int i = 0; i < PKT_MAX; ++i)
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler
{
	RegisterHandler(int pktType, HandlerFunc handler)
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(ClientSession* session); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(ClientSession* session)

//@}



///////////////////////////////////////////////////////////////////////////
/*
	연결된 클라이언트와 패킷 받고 보내는 작업 완료하는 콜백 함수들
	*/
///////////////////////////////////////////////////////////////////////////
void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	/// 받은 데이터 처리
	fromClient->OnRead(cbTransferred);

	/// 다시 받기
	if (false == fromClient->PostRecv())
	{
		fromClient->Disconnect();
		return;
	}
}
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	fromClient->OnWriteComplete(cbTransferred);

}


///////////////////////////////////////////////////////////////////////////
/*
	보내기 완료한 패킷을 출력버퍼에서 제거하는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnWriteComplete(size_t len)
{
	mSendBuffer.Remove(len);
}

///////////////////////////////////////////////////////////////////////////
/*
	받은 패킷 파싱하여 처리하는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len);

	/// 패킷 파싱하고 처리
	while (true)
	{
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader header;
		if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			return;

		/// 패킷 완성이 되는가? 
		if (mRecvBuffer.GetStoredSize() < (size_t)header.mSize)
			return;


		if (header.mType >= PKT_MAX || header.mType <= PKT_NONE)
		{
			printf("[DEBUG] Invalid packet type", GetPlayerId());
			Disconnect();
			return;
		}

		/// packet dispatch...
		HandlerTable[header.mType](this);
	}
}

///////////////////////////////////////////////////////////////////////////
/*
	패킷 타입에 따라 파싱을 완료하고 작업을 처리하는 핸들러들
	*/
///////////////////////////////////////////////////////////////////////////
REGISTER_HANDLER(PKT_CS_LOGIN)
{
	LoginRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}
	printf("\n Request Login ID: %d \n", inPacket.mPlayerId);
	session->LoginSuccessInform(inPacket.mPlayerId);

	// 	LoadPlayerDataContext* newDbJob = new LoadPlayerDataContext(session->GetSocketKey(), inPacket.mPlayerId);
	// 	GDatabaseJobManager->PushDatabaseJobRequest(newDbJob);
}

REGISTER_HANDLER(PKT_CS_MAKE_ROOM)
{
	MakeRoomRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}
	printf("\n Request MakeRoom from %d \n", inPacket.mPlayerId);
	session->MakeGameRoom(inPacket.mPlayerId);
}

REGISTER_HANDLER(PKT_CS_INOUT_ROOM)
{
	InOutRoomRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}

	if (session->GetPlayerId() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error!");
		return;
	}

	if (inPacket.mIsIn)
	{
		printf("\n Request JoinRoom from %d \n", inPacket.mPlayerId);
		session->JoinGameRoom();
	}
	else
	{
		printf("\n Request OutRoom from %d \n", inPacket.mPlayerId);
		session->OutGameRoom();
	}
	
}



REGISTER_HANDLER(PKT_CS_CREATE_HERO)
{
	CreateHeroRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}

	printf("\n haveID: %d \n recvID: %d \n", session->GetPlayerId(), inPacket.mPlayerId);

	if (inPacket.mPlayerId != session->GetPlayerId())
	{
		printf("[DEBUG] PKT_CS_CREATE_HERO: invalid player ID", session->GetPlayerId());
		return;
	}

	CreateHeroResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mUnitId = inPacket.mUnitId;
	outPacket.mPosX = inPacket.mPosX;
	outPacket.mPosY = inPacket.mPosY;

	if (!session->Broadcast(&outPacket))
	{
		session->Disconnect();
	}
}





REGISTER_HANDLER(PKT_CS_CHAT)
{
	ChatBroadcastRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}

	if (inPacket.mPlayerId != session->GetPlayerId())
	{
		printf("[DEBUG] PKT_CS_CHAT: invalid player ID", session->GetPlayerId());
		return;
	}

	/// chatting의 경우 여기서 바로 방송

	ChatBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	strcpy_s(outPacket.mName, session->GetPlayerName());
	strcpy_s(outPacket.mChat, inPacket.mChat);

	/// 채팅은 바로 방송 하면 끝
	if (!session->Broadcast(&outPacket))
	{
		session->Disconnect();
	}
}

REGISTER_HANDLER(PKT_CS_MOVE)
{
	MoveRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d", inPacket.mType);
		return;
	}

	if (inPacket.mPlayerId != session->GetPlayerId())
	{
		printf("[DEBUG] PKT_CS_MOVE: invalid player ID", session->GetPlayerId());
		return;
	}

	MoveBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mPosX = inPacket.mPosX;
	outPacket.mPosY = inPacket.mPosY;

	if (!session->Broadcast(&outPacket))
	{
		session->Disconnect();
	}

}



///////////////////////////////////////////////////////////////////////////
/*
	보낼 패킷 파싱하는 함수들
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::LoginSuccessInform(int id)
{
	LoginResult outPacket;

	outPacket.mPlayerId = mPlayerId = id;

	// 여기서는 일단 ID로 닉네임을 덮어썼는데,
	// 나중에 DB를 이용해 ID별로 닉네임을 적용해야 할듯. -수빈
	itoa(mPlayerId, mPlayerName, 10);
	strcpy_s(outPacket.mName, mPlayerName);

	SendRequest(&outPacket);

	mLogon = true;

	printf(" Soket: %d \n", mSocket);
	printf(" ClntAddr: %s \n", inet_ntoa(mClientAddr.sin_addr));
	printf(" ClntPort: %d \n", ntohs(mClientAddr.sin_port));
	printf(" Send Login ID: %d \n", outPacket.mPlayerId);
	printf(" Send Login Name: %s \n\n", outPacket.mName);
}

void ClientSession::MakeGameRoom(int id)
{
	GameRoom* gameRoom = GGameManager->CreateRoom();
	MakeRoomResult outPacket;

	outPacket.mPlayerId = mPlayerId = id;
	outPacket.mRoomId = mRoomId = gameRoom->GetRoomID();

	SendRequest(&outPacket);

	printf(" Send Login ID: %d \n", outPacket.mPlayerId);
	printf(" Send Room ID: %d \n", outPacket.mRoomId);
}

void ClientSession::JoinGameRoom()
{
	auto roomNum = GGameManager->SearchRoom();
	
	if (roomNum == -1)
		return;

	GGameManager->JoinRoom(mPlayerId, mRoomId);

	InOutRoomResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mRoomId = mRoomId;

	SendRequest(&outPacket);

	printf(" Send JoinRoomID: %d \n", outPacket.mRoomId);
}

void ClientSession::OutGameRoom()
{
	GGameManager->OutRoom(mPlayerId, mRoomId);
}

