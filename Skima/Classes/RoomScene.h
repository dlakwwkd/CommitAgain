#pragma once
#include "cocos2d.h"

USING_NS_CC;

class RoomScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);

	void SetRoomID(int id) { m_RoomID = id; };

	void menuCallback1(Ref* sender); //게임시작
	void menuCallback2(Ref* sender); //나가기

	void Tick(float dt);

	void GameStartComplete(); //서버시작한다
private:
	int m_RoomID;
};
