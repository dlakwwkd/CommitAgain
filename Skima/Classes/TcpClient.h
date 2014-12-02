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

#define GET_NETWORK_SCENE   dynamic_cast<NetworkScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("NetworkScene"))
#define GET_ROOM_SCENE      dynamic_cast<RoomScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("RoomScene"))
#define GET_M_GAME_SCENE    dynamic_cast<MultiGameScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("MultiGameScene"))
#define GET_LOADING_LAYER   dynamic_cast<LoadingBGLayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("MultiGameScene")->getChildByName("LoadingBGLayer"))
#define GET_OBJECT_LAYER    dynamic_cast<ObjectLayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("MultiGameScene")->getChildByName("ListenerLayer")->getChildByName("ObjectLayer"))

#define CONVERT(v) {(v).x, (v).y}

class TcpClient
{
public:
    static TcpClient* getInstance();
    static void destroyInstance();

    SOCKET  checkSocket(){ return mSock; }
    int     getLoginId(){ return mLoginId; }
    bool connect();
    void disconnect();

    void loginRequest();
    void makeRoomRequest();
    void joinRoomRequest();
    void outRoomRequest(int roomId);
    void startGameRequest();
    void runCompleteRequest(); //이름 체인지 + bool값 인자

    void moveRequest(Vec2 curPos, Vec2 targetPos);
    void skillRequest(Vec2 curPos, Vec2 targetPos, SkillKey skillKey);
    void splashSkillRequest(Vec2 curPos, Vec2 targetPos, SkillKey skillKey);

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
};

