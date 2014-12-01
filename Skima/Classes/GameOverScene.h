#pragma once

USING_NS_CC;

class GameOverScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);

	void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);

	void Tick(float dt);

	void SetRoomID(int id) { m_RoomID = id; };

	void GameStartComplete();

private:

};
