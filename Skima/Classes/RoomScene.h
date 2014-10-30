#pragma once
#include "cocos2d.h"

USING_NS_CC;

class RoomScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);

	void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);

	void makeRoomComplit(int roomId);

private:
	int m_RoomID;
};
