#pragma once
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
	void			ScreenMove();

	virtual void	OnMouseDown(Event *event);
	virtual void	OnMouseUp(Event *event);
	virtual void	OnMouseMove(Event *event);
	virtual void	OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void	OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


private:
	bool			m_Targeting;
};

