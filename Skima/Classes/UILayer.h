#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UILayer);

	void doClick1(Ref* sender);
	void loadingMessage();
};

