#include "pch.h"
#include "PhysicsLayer.h"
#include "GameManager.h"
#include "ObjectLayer.h"
#include "MapLayer.h"
#include "TcpClient.h"

#define GET_OBJECT_LAYER dynamic_cast<ObjectLayer*>(this->getChildByName("ObjectLayer"))

bool PhysicsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto layer1 = MapLayer::create();
	auto layer2 = ObjectLayer::create();
	this->addChild(layer1, 0, "MapLayer");
	this->addChild(layer2, 1, "ObjectLayer");
	layer2->schedule(schedule_selector(ObjectLayer::TickS));

	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseDown = CC_CALLBACK_1(PhysicsLayer::OnMouseDown, this);
	MouseListener->onMouseUp = CC_CALLBACK_1(PhysicsLayer::OnMouseUp, this);
	MouseListener->onMouseMove = CC_CALLBACK_1(PhysicsLayer::OnMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

	auto K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(PhysicsLayer::OnKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(PhysicsLayer::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);

	this->schedule(schedule_selector(PhysicsLayer::Tick));
	return true;
}

//////////////////////////////////////////////////////////////////////////
void PhysicsLayer::Tick(float dt)
{
	UpdateKeyInput();
	auto layer = GET_OBJECT_LAYER;			_ASSERT(layer != nullptr);
	layer->MobAi();
	ScreenMove();
}
//////////////////////////////////////////////////////////////////////////


void PhysicsLayer::UpdateKeyInput()
{
	if (GET_IM->GetKeyStatus(KEY_UP_ARROW))
		this->setPositionY(this->getPositionY() - 10);
	if (GET_IM->GetKeyStatus(KEY_DOWN_ARROW))
		this->setPositionY(this->getPositionY() + 10);
	if (GET_IM->GetKeyStatus(KEY_LEFT_ARROW))
		this->setPositionX(this->getPositionX() + 10);
	if (GET_IM->GetKeyStatus(KEY_RIGHT_ARROW))
		this->setPositionX(this->getPositionX() - 10);
}

void PhysicsLayer::ScreenMove()
{
	if (GET_IM->GetMouseScrollStatus(SCROLL_UP)){
		this->setPositionY(this->getPositionY() + 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_DOWN)){
		this->setPositionY(this->getPositionY() - 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_LEFT)){
		this->setPositionX(this->getPositionX() + 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_RIGHT)){
		this->setPositionX(this->getPositionX() - 10);
	}
}




///////////////////////////////////////////////////////////////////////////
/*
	마우스 리스너
*/
///////////////////////////////////////////////////////////////////////////
void PhysicsLayer::OnMouseDown(Event *event)
{
	auto button = static_cast<EventMouse*>(event)->getMouseButton();
	GET_IM->SetMouseStatus(button, true);

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		break;
	case MOUSE_BUTTON_RIGHT:
		auto layer = GET_OBJECT_LAYER;		_ASSERT(layer != nullptr);
		layer->UnitMove(1, { 0, 0 }, GET_IM->GetMouseLocation());
		break;
	}
}

void PhysicsLayer::OnMouseUp(Event *event)
{
	auto button = static_cast<EventMouse*>(event)->getMouseButton();
	GET_IM->SetMouseStatus(button, false);
}

void PhysicsLayer::OnMouseMove(Event *event)
{
	auto location = static_cast<EventMouse*>(event)->getLocation();
	location.y = Director::getInstance()->getWinSize().height - location.y;

	GET_IM->SetMouseLocation(location);
	GET_IM->CheckMouseScroll();

	if (GET_IM->GetMouseStatus(MOUSE_BUTTON_LEFT))
	{
		auto layer = GET_OBJECT_LAYER;		_ASSERT(layer != nullptr);
		layer->AddNewSpriteAtPosition(GET_IM->GetMouseLocation());
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	키보드 리스너
*/
///////////////////////////////////////////////////////////////////////////
void PhysicsLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, true);
}

void PhysicsLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, false);
}