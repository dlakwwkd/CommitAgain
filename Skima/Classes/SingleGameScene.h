#pragma once

USING_NS_CC;

class SingleGameScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SingleGameScene);
};
