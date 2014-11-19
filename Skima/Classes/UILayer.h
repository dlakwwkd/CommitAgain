#pragma once

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UILayer);

	void ClickExit(Ref* sender);
	void loadingMessage();
	
};

