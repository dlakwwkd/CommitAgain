#pragma once
#include "cocos2d.h"

USING_NS_CC;

class RoomScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);

	void menuCallback1(Ref* sender); //���ӽ���
	void menuCallback2(Ref* sender); //������

	void gameStartComplete(); //���������Ѵ�

	void makeRoomComplete(int roomId); //������ �Ⱦ���


	void SetRoomID(int id) { m_RoomID = id;};

private:
	int m_RoomID;
};
