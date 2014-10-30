#pragma once
#include "cocos2d.h"

USING_NS_CC;

class NetworkScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NetworkScene);

	void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);
	void menuCallback3(Ref* sender);

	void connectComplit();
	

private:
	int m_PlayerID;
	int m_RoomID;
	int m_GameID;
};

