#include "PhysicsLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"



bool PhysicsLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto layer1 = MapLayer::create();
	this->addChild(layer1, 0, "MapLayer");
	auto layer2 = ObjectLayer::create();
	this->addChild(layer2, 1, "ObjectLayer");

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
	CameraSync();
	auto child = (ObjectLayer*)(this->getChildByName("ObjectLayer"));
	child->MobAi();
}
//////////////////////////////////////////////////////////////////////////


void PhysicsLayer::OnMouseDown(Event *event)
{
	auto button = ((EventMouse*)event)->getMouseButton();
	GET_IM->SetMouseStatus(button, true);
	float x, y;

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		break;
	case MOUSE_BUTTON_RIGHT:
// 		auto child = (ObjectLayer*)(this->getChildByName("ObjectLayer"));
// 		child->UnitMove(GET_IM->GetMouseLocation());
				
		 x = GET_IM->GetMouseLocation().x;
		 y = GET_IM->GetMouseLocation().y;

		TcpClient::getInstance()->moveRequest(x,y);
		
		break;
	}
}

void PhysicsLayer::OnMouseUp(Event *event)
{
	auto button = ((EventMouse*)event)->getMouseButton();
	GET_IM->SetMouseStatus(button, false);
}

void PhysicsLayer::OnMouseMove(Event *event)
{
	auto location = ((EventMouse*)event)->getLocation();
	location.y = Director::getInstance()->getWinSize().height - location.y;

	GET_IM->SetMouseLocation(location);


	if (GET_IM->GetMouseStatus(MOUSE_BUTTON_LEFT))
	{
		auto child = (ObjectLayer*)(this->getChildByName("ObjectLayer"));
		child->AddNewSpriteAtPosition(GET_IM->GetMouseLocation());
	}
	
}


void PhysicsLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, true);
}

void PhysicsLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, false);
}

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

void PhysicsLayer::CameraSync()
{

}
