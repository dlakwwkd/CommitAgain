#pragma once
#include "Enums.h"
#include "PacketType.h"

USING_NS_CC;

class GameScene : public Layer
{
public:

    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

	void        SetRoomInfo(RoomInfo roomInfo) { m_RoomInfo = roomInfo; }
    RoomInfo    GetRoomInfo(){ return m_RoomInfo; }
    int         GetRoomID(){ return m_RoomInfo.mRoomNum; }
    bool        IsStartGame(){ return m_IsStartGame; }

    void        StartGame();
    void        RemoveLoadingLayer();
    void        GameOver(int playerId, int loseId);

private:
    bool	    m_IsStartGame;
    RoomInfo    m_RoomInfo;
};
