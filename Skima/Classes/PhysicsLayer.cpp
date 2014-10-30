#include "PhysicsLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "Enums.h"



bool PhysicsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto layer1 = MapLayer::create();
	this->addChild(layer1, 0, "Map Layer");
	auto layer2 = ObjectLayer::create();
	this->addChild(layer2, 1, "Object Layer");

	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseDown = CC_CALLBACK_1(PhysicsLayer::onMouseDown, this);
	MouseListener->onMouseUp = CC_CALLBACK_1(PhysicsLayer::onMouseUp, this);
	MouseListener->onMouseMove = CC_CALLBACK_1(PhysicsLayer::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

	auto K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(PhysicsLayer::onKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(PhysicsLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);

	this->schedule(schedule_selector(PhysicsLayer::tick));
	return true;
}

void PhysicsLayer::tick(float dt)
{
	updateKeyInput();
	cameraSync();
	auto child = (ObjectLayer*)(this->getChildByName("Object Layer"));
	child->MobAi();
}


void PhysicsLayer::onMouseDown(Event *event)
{
	auto button = ((EventMouse*)event)->getMouseButton();
	GET_IM->setMouseStatus(button, true);

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		break;
	case MOUSE_BUTTON_RIGHT:
		auto child = (ObjectLayer*)(this->getChildByName("Object Layer"));
		child->unitMove(GET_IM->getMouseLocation());
		break;
	}
}

void PhysicsLayer::onMouseUp(Event *event)
{
	auto button = ((EventMouse*)event)->getMouseButton();
	GET_IM->setMouseStatus(button, false);
}

void PhysicsLayer::onMouseMove(Event *event)
{
	auto location = ((EventMouse*)event)->getLocation();
	location.y = Director::getInstance()->getWinSize().height - location.y;

	GET_IM->setMouseLocation(location);

	
	if (GET_IM->getMouseStatus(MOUSE_BUTTON_LEFT))
	{
		auto child = (ObjectLayer*)(this->getChildByName("Object Layer"));
		child->addNewSpriteAtPosition(GET_IM->getMouseLocation());
	}
}


void PhysicsLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->setKeyStatus(keyCode, true);
}

void PhysicsLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->setKeyStatus(keyCode, false);
}

void PhysicsLayer::updateKeyInput()
{
	if (GET_IM->getKeyStatus(KEY_UP_ARROW))
		this->setPositionY(this->getPositionY() - 10);
	if (GET_IM->getKeyStatus(KEY_DOWN_ARROW))
		this->setPositionY(this->getPositionY() + 10);
	if (GET_IM->getKeyStatus(KEY_LEFT_ARROW))
		this->setPositionX(this->getPositionX() + 10);
	if (GET_IM->getKeyStatus(KEY_RIGHT_ARROW))
		this->setPositionX(this->getPositionX() - 10);
}

void PhysicsLayer::cameraSync()
{
	
}
