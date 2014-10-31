#pragma once
#include "cocos2d.h"
#include "TcpClient.h"


USING_NS_CC;

class PhysicsLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PhysicsLayer);

	PhysicsWorld*	GetPhyWorld()					{ return m_World; }
	void			SetPhyWorld(PhysicsWorld* world){ m_World = world; }

	void			Tick(float dt);
	void			UpdateKeyInput();
	void			CameraSync();

	virtual void	OnMouseDown(Event *event);
	virtual void	OnMouseUp(Event *event);
	virtual void	OnMouseMove(Event *event);
	virtual void	OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void	OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

protected:
	PhysicsWorld*	m_World;

};

