#pragma once
#include <string>
#include "CircularBuffer.h"
#include "PacketType.h"

#ifndef _WIN32
#include <netdb.h>
#include <unistd.h>
#else
#include <winsock2.h>
#endif

USING_NS_CC;

#define BUF_SIZE    32768

class TcpClient
{
public:
    static TcpClient* getInstance();
    static void destroyInstance();

    SOCKET  checkSocket(){ return mSock; }
    int     getLoginId(){ return mLoginId; }
    Team    getTeam(){ return mTeam; }
    bool    connect();
    void    disconnect();
    void    SetServIP(std::string servIP){ mServIP = servIP; }
    std::string GetServIP(){ return mServIP; }

    void    loginRequest(const char* playerName);
    void    makeRoomRequest(RoomInfo roomInfo);
    void    joinRoomRequest(RoomInfo roomInfo);
    void    outRoomRequest(RoomInfo roomInfo);
    void    startGameRequest(int roomId, Team team, HeroType heroType);
    void    runCompleteRequest(); //이름 체인지 + bool값 인자

    void    moveRequest(Vec2 curPos, Vec2 targetPos);
    void    skillRequest(Vec2 curPos, Vec2 targetPos, SkillKey skillKey);
    void    splashSkillRequest(Vec2 curPos, Vec2 targetPos, SkillKey skillKey);

//	void chatRequest(const char* chat);

private:
    TcpClient();
    virtual ~TcpClient();

    bool send(const char* data, int length);
    void networkThread();
    void processPacket();

private:
    SOCKET          mSock;
    CircularBuffer  mRecvBuffer;
    int             mLoginId;
    char            mLoginName[MAX_NAME_LEN];
    Team            mTeam;
    std::string     mServIP;
};

