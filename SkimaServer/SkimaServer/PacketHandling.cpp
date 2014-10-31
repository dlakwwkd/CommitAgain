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
	����� Ŭ���̾�Ʈ�� ��Ŷ �ް� ������ �۾� �Ϸ��ϴ� �ݹ� �Լ���
	*/
///////////////////////////////////////////////////////////////////////////
void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// ���� �߻��� �ش� ���� ����
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	/// ���� ������ ó��
	fromClient->OnRead(cbTransferred);

	/// �ٽ� �ޱ�
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

	/// ���� �߻��� �ش� ���� ����
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	fromClient->OnWriteComplete(cbTransferred);

}


///////////////////////////////////////////////////////////////////////////
/*
	������ �Ϸ��� ��Ŷ�� ��¹��ۿ��� �����ϴ� �Լ�
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnWriteComplete(size_t len)
{
	mSendBuffer.Remove(len);
}

///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ �Ľ��Ͽ� ó���ϴ� �Լ�
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len);

	/// ��Ŷ �Ľ��ϰ� ó��
	while (true)
	{
		/// ��Ŷ ��� ũ�� ��ŭ �о�ͺ���
		PacketHeader header;
		if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			return;

		/// ��Ŷ �ϼ��� �Ǵ°�? 
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
	��Ŷ Ÿ�Կ� ���� �Ľ��� �Ϸ��ϰ� �۾��� ó���ϴ� �ڵ鷯��
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

	/// chatting�� ��� ���⼭ �ٷ� ���

	ChatBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	strcpy_s(outPacket.mName, session->GetPlayerName());
	strcpy_s(outPacket.mChat, inPacket.mChat);

	/// ä���� �ٷ� ��� �ϸ� ��
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
	���� ��Ŷ �Ľ��ϴ� �Լ���
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::LoginSuccessInform(int id)
{
	LoginResult outPacket;

	outPacket.mPlayerId = mPlayerId = id;

	// ���⼭�� �ϴ� ID�� �г����� �����µ�,
	// ���߿� DB�� �̿��� ID���� �г����� �����ؾ� �ҵ�. -����
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

