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

	void menuCallback1(Ref* sender); //���ӽ���
	void menuCallback2(Ref* sender); //������

	void Tick(float dt);

	void GameStartComplete(); //���������Ѵ�
private:
	int m_RoomID;
};
