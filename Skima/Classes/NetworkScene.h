#pragma once

USING_NS_CC;

class NetworkScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NetworkScene);

	void menuCallback0(Ref* sender);
	void menuCallback1(Ref* sender);
	void menuCallback2(Ref* sender);
	void menuCallback3(Ref* sender);

	void Tick(float dt);

	void ConnectLabelCreate(const char* str, NetworkScene* scene);
	void ConnectLabelChange(const char* str);
	void MakeRoomComplete(int roomId);
	void JoinRoomComplete(int roomId);
};

