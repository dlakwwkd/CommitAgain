#include "stdafx.h"
#include "Scheduler.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"
//#include "DatabaseJobContext.h"
//#include "DatabaseJobManager.h"



///////////////////////////////////////////////////////////////////////////
/*
	연결요청 들어온 클라와의 연결 처리 완료
*/
///////////////////////////////////////////////////////////////////////////
bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	memcpy(&mClientAddr, addr, sizeof(SOCKADDR_IN));

	/// 소켓을 넌블러킹으로 바꾸고
	u_long arg = 1;
	ioctlsocket(mSocket, FIONBIO, &arg);

	/// nagle 알고리즘 끄기
	int opt = 1;
	setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));

	printf("[DEBUG] Client Connected: IP = %s, PORT = %d\n", inet_ntoa(mClientAddr.sin_addr), ntohs(mClientAddr.sin_port));
	
	mConnected = true;
	OnTick();
	return PostRecv();
}

///////////////////////////////////////////////////////////////////////////
/*
	연결 완료된 클라에게서 입력 받을 준비 완료
*/
///////////////////////////////////////////////////////////////////////////
bool ClientSession::PostRecv()
{
	if (!IsConnected())
		return false;

	DWORD recvbytes = 0;
	DWORD flags = 0;
	WSABUF buf;
	buf.len = (ULONG)mRecvBuffer.GetFreeSpaceSize();
	buf.buf = (char*)mRecvBuffer.GetBuffer();

	memset(&mOverlappedRecv, 0, sizeof(OverlappedIO));
	mOverlappedRecv.mObject = this;

	/// 비동기 입출력 시작
	if (SOCKET_ERROR == WSARecv(mSocket, &buf, 1, &recvbytes, &flags, &mOverlappedRecv, RecvCompletion))
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
			return false;
	}

	IncRefCount();

	return true;
}

///////////////////////////////////////////////////////////////////////////
/*
	연결 해제 처리 함수
*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::Disconnect()
{
	if (!IsConnected())
		return;

	printf("[DEBUG] Client Disconnected: IP = %s, PORT = %d\n", inet_ntoa(mClientAddr.sin_addr), ntohs(mClientAddr.sin_port));

	/// 즉각 해제

	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;

	/// no TCP TIME_WAIT
	if (SOCKET_ERROR == setsockopt(mSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{
		printf_s("[DEBUG] setsockopt linger option error: %d\n", GetLastError());
		return;
	}

	closesocket(mSocket);

	mConnected = false;
	
	OutGameRoom();

}



///////////////////////////////////////////////////////////////////////////
/*
	보낼 패킷 출력버퍼에 쌓아놓기
*/
///////////////////////////////////////////////////////////////////////////
bool ClientSession::SendRequest(PacketHeader* pkt)
{
	if (!IsConnected())
		return false;

	/// Send 요청은 버퍼에 쌓아놨다가 한번에 보낸다.
	if (false == mSendBuffer.Write((char*)pkt, pkt->mSize))
	{
		/// 버퍼 용량 부족인 경우는 끊어버림
		Disconnect();
		return false;
	}

	return true;

}

///////////////////////////////////////////////////////////////////////////
/*
	출력버퍼에 쌓여있는 패킷 전부 전송하기
*/
///////////////////////////////////////////////////////////////////////////
bool ClientSession::SendFlush()
{
	if (!IsConnected())
		return false;

	/// 보낼 데이터가 없으면 그냥 리턴
	if (mSendBuffer.GetContiguiousBytes() == 0)
		return true;

	DWORD sendbytes = 0;
	DWORD flags = 0;

	WSABUF buf;
	buf.len = (ULONG)mSendBuffer.GetContiguiousBytes();
	buf.buf = (char*)mSendBuffer.GetBufferStart();

	memset(&mOverlappedSend, 0, sizeof(OverlappedIO));
	mOverlappedSend.mObject = this;

	/// 비동기 입출력 시작
	if (SOCKET_ERROR == WSASend(mSocket, &buf, 1, &sendbytes, flags, &mOverlappedSend, SendCompletion))
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
			return false;
	}

	IncRefCount();

	return true;
}



///////////////////////////////////////////////////////////////////////////
/*
	동일한 패킷을 연결된 모든 클라의 출력버퍼에 넣어놓는 함수
	(먼저 이 함수를 실행한 클라에게 넣고,
	 클라이언트 매니저를 통해	 다른 모든 클라의 출력버퍼에 넣는다.)
*/
///////////////////////////////////////////////////////////////////////////
bool ClientSession::Broadcast(PacketHeader* pkt)
{
	if (!SendRequest(pkt))
		return false;

	if (!IsConnected())
		return false;

	GClientManager->BroadcastPacket(this, pkt);

	return true;
}


///////////////////////////////////////////////////////////////////////////
/*
	PLAYER_HEART_BEAT 주기마다 클라별로 처리할 작업 등록하는 곳
*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnTick()
{
	if (!IsConnected())
		return;

	//////////////////////////////////////////////////////////////////////////
	///여기에 등록



	//////////////////////////////////////////////////////////////////////////
	
	CallFuncAfter(PLAYER_HEART_BEAT, this, &ClientSession::OnTick);
}








/*
	DB 작업
*/
// 
// void ClientSession::OnDbUpdate()
// {
// 	if (!IsConnected())
// 		return;
// 
// 	UpdatePlayerDataContext* updatePlayer = new UpdatePlayerDataContext(mSocket, mPlayerId) ;
// 	 
// 	strcpy_s(updatePlayer->mComment, "updated_test") ; ///< 일단은 테스트를 위한 코멘트
// 	GDatabaseJobManager->PushDatabaseJobRequest(updatePlayer) ;
// 
// 	CallFuncAfter(PLAYER_DB_UPDATE_INTERVAL, this, &ClientSession::OnDbUpdate);
// 
// }
// 
// 
// void ClientSession::DatabaseJobDone(DatabaseJobContext* result)
// {
// 	CRASH_ASSERT( mSocket == result->mSockKey ) ;
// 	
// 
// 	const type_info& typeInfo = typeid(*result) ;
// 
// 	if ( typeInfo == typeid(LoadPlayerDataContext) )
// 	{
// 		LoadPlayerDataContext* login = dynamic_cast<LoadPlayerDataContext*>(result) ;
// 
// 		LoginDone(login->mPlayerId, login->mPlayerName) ;
// 	
// 	}
// 	else if ( typeInfo == typeid(UpdatePlayerDataContext) )
// 	{
// 		UpdateDone() ;
// 	}
// 	else
// 	{
// 		CRASH_ASSERT(false) ;
// 	}
// 
// }
// 
// void ClientSession::UpdateDone()
// {
// 	/// 콘텐츠를 넣기 전까지는 딱히 해줄 것이 없다. 단지 테스트를 위해서..
// 	printf("Player[%d] Update Done\n", mPlayerId) ;
// }
// 
// 
// 
// void ClientSession::LoginDone(int pid, const char* name)
// {
// // 	LoginResult outPacket;
// // 
// // 	outPacket.mPlayerId = mPlayerId = pid;
// // 	strcpy_s(mPlayerName, name);
// // 	strcpy_s(outPacket.mName, name);
// // 
// // 	SendRequest(&outPacket);
// // 
// // 	mLogon = true;
// // 
// // 	/// heartbeat gogo
// // 	OnTick();
// // 
// // 	/// first db update gogo
// // 	OnDbUpdate();
// }
