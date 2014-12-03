#pragma once
#include "Enums.h"

USING_NS_CC;

class GameOverScene : public LayerColor
{
public:
	static Scene* createScene(int roomId, int playerId, int loseId);
	virtual bool init();
	CREATE_FUNC(GameOverScene);

	void SetRoomID(int id) { m_RoomId = id; };

	void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);

private:
	int m_RoomId;
};
