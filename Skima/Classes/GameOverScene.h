#pragma once
#include "Enums.h"
#include "PacketType.h"

USING_NS_CC;

class GameOverScene : public LayerColor
{
public:
    static Scene* createScene(RoomInfo roomInfo, int playerId, bool isWin);
	virtual bool init();
	CREATE_FUNC(GameOverScene);

	void SetRoomInfo(RoomInfo roomInfo) { m_RoomInfo = roomInfo; };

	//void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);

private:
    RoomInfo m_RoomInfo;
};
