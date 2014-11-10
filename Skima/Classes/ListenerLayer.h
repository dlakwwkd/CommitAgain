#pragma once
#include "cocos2d.h"
#include "TcpClient.h"
#include "InputManager.h"

USING_NS_CC;

class ListenerLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ListenerLayer);
		
	void			Tick(float dt);
	void			UpdateKeyInput();
	void			CameraSync();

	void			ScreenMove();
	virtual void	OnMouseDown(Event *event);
	virtual void	OnMouseUp(Event *event);
	virtual void	OnMouseMove(Event *event);
	virtual void	OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void	OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

