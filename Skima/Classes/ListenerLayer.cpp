#include "ListenerLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "MultiGameScene.h"
#include "Unit.h"


bool ListenerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto layer1 = MapLayer::create();
	auto layer2 = ObjectLayer::create();
	this->addChild(layer1, 0, "MapLayer");
	this->addChild(layer2, 1, "ObjectLayer");
	layer2->schedule(schedule_selector(ObjectLayer::TickM), 0.016f);

	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseDown = CC_CALLBACK_1(ListenerLayer::OnMouseDown, this);
	MouseListener->onMouseUp = CC_CALLBACK_1(ListenerLayer::OnMouseUp, this);
	MouseListener->onMouseMove = CC_CALLBACK_1(ListenerLayer::OnMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

	auto K_listener = EventListenerKeyboard::create();
	K_listener->onKeyPressed = CC_CALLBACK_2(ListenerLayer::OnKeyPressed, this);
	K_listener->onKeyReleased = CC_CALLBACK_2(ListenerLayer::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listener, this);

	this->schedule(schedule_selector(ListenerLayer::Tick));
	return true;
}

//////////////////////////////////////////////////////////////////////////
void ListenerLayer::Tick(float dt)
{
	//ScreenMove();
}
//////////////////////////////////////////////////////////////////////////


void ListenerLayer::UpdateKeyInput()
{

}

void ListenerLayer::CameraSync()
{

}


void ListenerLayer::OnMouseDown(Event *event)
{
	if (!dynamic_cast<MultiGameScene*>(this->getParent())->IsStartGame())
		return;

	auto button = dynamic_cast<EventMouse*>(event)->getMouseButton();
	GET_IM->SetMouseStatus(button, true);

	auto layer = dynamic_cast<ObjectLayer*>(this->getChildByName("ObjectLayer"));
	auto hero = layer->GetMyHero();

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		break;
	case MOUSE_BUTTON_RIGHT:
		if (hero->GetMoveState() != hero->GetCrashedState())
		{
			TcpClient::getInstance()->moveRequest(hero->GetSprite()->getPosition(), GET_IM->GetMouseLocation());
		}
		break;
	}
}

void ListenerLayer::OnMouseUp(Event *event)
{
	auto button = dynamic_cast<EventMouse*>(event)->getMouseButton();
	GET_IM->SetMouseStatus(button, false);
}

void ListenerLayer::OnMouseMove(Event *event)
{
	auto location = dynamic_cast<EventMouse*>(event)->getLocation();
	location.y = Director::getInstance()->getWinSize().height - location.y;

	GET_IM->SetMouseLocation(location);
	GET_IM->CheckMouseScroll();
}


void ListenerLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, true);
}

void ListenerLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, false);
}

void ListenerLayer::ScreenMove()
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
	if (GET_IM->GetMouseScrollStatus(SCROLL_UPRIGHT)){
		this->setPositionY(this->getPositionY() + 10);
		this->setPositionX(this->getPositionX() - 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_UPLEFT)){
		this->setPositionY(this->getPositionY() + 10);
		this->setPositionX(this->getPositionX() + 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_DOWNLEFT)){
		this->setPositionY(this->getPositionY() - 10);
		this->setPositionX(this->getPositionX() + 10);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_DOWNRIGHT)){
		this->setPositionY(this->getPositionY() - 10);
		this->setPositionX(this->getPositionX() - 10);
	}
}
