#pragma once
#include "cocos2d.h"
#include "TcpClient.h"


USING_NS_CC;

class PhysicsLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PhysicsLayer);

	PhysicsWorld*	getPhyWorld()					{ return m_World; }
	void			setPhyWorld(PhysicsWorld* world){ m_World = world; }

	void			tick(float dt);
	void			updateKeyInput();
	void			cameraSync();

	virtual void	onMouseDown(Event *event);
	virtual void	onMouseUp(Event *event);
	virtual void	onMouseMove(Event *event);
	virtual void	onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void	onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

protected:
	PhysicsWorld*	m_World;

};

