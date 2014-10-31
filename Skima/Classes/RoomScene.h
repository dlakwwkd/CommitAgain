#pragma once
#include "cocos2d.h"

USING_NS_CC;

class RoomScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);

	void menuCallback1(Ref* sender); //게임시작
	void menuCallback2(Ref* sender); //나가기

	void gameStartComplete(); //서버시작한다

	void makeRoomComplete(int roomId); //아직은 안쓰임


	void SetRoomID(int id) { m_RoomID = id;};

private:
	int m_RoomID;
};
