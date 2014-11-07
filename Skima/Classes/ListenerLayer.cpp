#include "ListenerLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "MultiGameScene.h"


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
	layer2->schedule(schedule_selector(ObjectLayer::TickM));

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
	auto child = dynamic_cast<ObjectLayer*>(this->getChildByName("ObjectLayer"));
	child->MobAi();
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
	float x, y;

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		break;
	case MOUSE_BUTTON_RIGHT:
		auto child = dynamic_cast<ObjectLayer*>(this->getChildByName("ObjectLayer"));
		child->UnitMove(GET_IM->GetMouseLocation(), MULTI);

		TcpClient::getInstance()->moveRequest(GET_IM->GetMouseLocation());
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
}


void ListenerLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, true);
}

void ListenerLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, false);
}
