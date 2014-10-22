#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MainScene : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

	void doClick1(Ref* sender);
	void doClick2(Ref* sender);
	void doClick3(Ref* sender);


};

