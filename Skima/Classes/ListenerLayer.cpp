#include "pch.h"
#include "ListenerLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "InputManager.h"
#include "MultiGameScene.h"
#include "Hero.h"
#include "UILayer.h"

#define GET_OBJECT_LAYER	dynamic_cast<ObjectLayer*>(this->getChildByName("ObjectLayer"))
#define GET_UI_LAYER		dynamic_cast<UILayer*>(this->getParent()->getChildByName("UILayer"))


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

	m_Targeting = false;

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

void ListenerLayer::ScreenMove()
{
	Point mouseLocation = GET_IM->GetMouseLocation();
	auto winSize = Director::getInstance()->getWinSize();

	if (GET_IM->GetMouseScrollStatus(SCROLL_LEFT) && GET_IM->GetMouseScrollStatus(SCROLL_UP))
	{
		Point creteria = { 50, 50 };
		Point gap = { abs(creteria.x - mouseLocation.x), abs(creteria.y - mouseLocation.y) };
		gap *= 7;
		this->setPosition(this->getPosition() + gap);

	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_RIGHT) && GET_IM->GetMouseScrollStatus(SCROLL_UP))
	{
		Point creteria = { winSize.width-50, 50 };
		Point gap = { abs(creteria.x - mouseLocation.x), abs(creteria.y - mouseLocation.y) };
		gap *= 7;
		this->setPositionX(this->getPositionX() - gap.x);
		this->setPositionY(this->getPositionY() + gap.y);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_RIGHT) && GET_IM->GetMouseScrollStatus(SCROLL_DOWN))
	{
		Point creteria = { winSize.width - 50, winSize.height - 50 };
		Point gap = { abs(creteria.x - mouseLocation.x), abs(creteria.y - mouseLocation.y) };
		gap *= 7;
		this->setPosition(this->getPosition() - gap);
	}
	if (GET_IM->GetMouseScrollStatus(SCROLL_LEFT) && GET_IM->GetMouseScrollStatus(SCROLL_DOWN))
	{
		Point creteria = { 50, winSize.height-50 };
		Point gap = { abs(creteria.x - mouseLocation.x), abs(creteria.y - mouseLocation.y) };
		gap *= 7;
		this->setPositionX(this->getPositionX() + gap.x);
		this->setPositionY(this->getPositionY() - gap.y);
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	마우스 리스너
*/
///////////////////////////////////////////////////////////////////////////
void ListenerLayer::OnMouseDown(Event *event)
{
	if (!dynamic_cast<MultiGameScene*>(this->getParent())->IsStartGame())
		return;

	auto button = dynamic_cast<EventMouse*>(event)->getMouseButton();
	GET_IM->SetMouseStatus(button, true);

	auto layer = GET_OBJECT_LAYER;						_ASSERT(layer != nullptr);
	auto hero = layer->GetMyHero();

	switch (button)
	{
	case MOUSE_BUTTON_LEFT:
		{
			if (!m_Targeting)
				break;
			auto key = GET_IM->SearchTargetingKey();		_ASSERT(key != EventKeyboard::KeyCode(-1));
			if (key != EventKeyboard::KeyCode(-1))
			{
				TcpClient::getInstance()->skillRequest(hero->GetSprite()->getPosition(), GET_IM->GetMouseLocation(),
					static_cast<SkillKey>(key));
			}
			GET_IM->InitTargetingKey();

			auto layer = GET_UI_LAYER;					_ASSERT(layer != nullptr);
			layer->CursorChange(CURSOR_DEFAULT);

			auto cursorShape = layer->GetCurrentShape();	_ASSERT(cursorShape != nullptr);
			cursorShape->setPosition(GET_IM->GetMouseLocation());

			CoolTimeStart(KeyboardToSkillKey(key));

			m_Targeting = false;
		}
		break;

	case MOUSE_BUTTON_RIGHT:
		{
			if (hero->GetMoveState() != hero->GetCrashedState())
			{
				TcpClient::getInstance()->moveRequest(hero->GetSprite()->getPosition(), GET_IM->GetMouseLocation());
			}
			GET_IM->InitTargetingKey();

			auto layer = GET_UI_LAYER;					_ASSERT(layer != nullptr);
			layer->CursorChange(CURSOR_DEFAULT);

			auto cursorShape = layer->GetCurrentShape();	_ASSERT(cursorShape != nullptr);
			cursorShape->setPosition(GET_IM->GetMouseLocation());

			m_Targeting = false;
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

	auto layer = GET_UI_LAYER;							_ASSERT(layer != nullptr);
	auto cursorShape = layer->GetCurrentShape();			_ASSERT(cursorShape != nullptr);
	cursorShape->setPosition(location);
}


///////////////////////////////////////////////////////////////////////////
/*
	키보드 리스너
*/
///////////////////////////////////////////////////////////////////////////
void ListenerLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, true);

	if (!(!m_Targeting && GET_OBJECT_LAYER->GetMyHero()->GetSkillCanUse(KeyboardToSkillKey(keyCode))))
		return;
	switch (keyCode)
	{
	case KEY_Q:
		{
			GET_IM->SetTargeting(keyCode, true);

			auto layer = GET_UI_LAYER;						_ASSERT(layer != nullptr);
			layer->CursorChange(CURSOR_ATTACK);

			auto cursorShape = layer->GetCurrentShape();		_ASSERT(cursorShape != nullptr);
			cursorShape->setPosition(GET_IM->GetMouseLocation());
		
			m_Targeting = true;
			break;
		}
	case KEY_W:
		{
			GET_IM->SetTargeting(keyCode, true);

			auto layer = GET_UI_LAYER;						_ASSERT(layer != nullptr);
			layer->CursorChange(CURSOR_ATTACK);

			auto cursorShape = layer->GetCurrentShape();		_ASSERT(cursorShape != nullptr);
			cursorShape->setPosition(GET_IM->GetMouseLocation());

			m_Targeting = true;
			break;
		}
	}
}

void ListenerLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GET_IM->SetKeyStatus(keyCode, false);
}




void ListenerLayer::CoolTimeStart(SkillKey key)
{
	Sprite* skillBlack;
	auto reduceWidth = ScaleBy::create(GET_OBJECT_LAYER->GetMyHero()->GetSkillCoolTime(key), 0.0f, 1.0f);
	auto coolTimeEnd = CallFunc::create(CC_CALLBACK_0(ListenerLayer::CoolTimeEnd, this, key));
	auto action = Sequence::create(reduceWidth, coolTimeEnd, NULL);

	switch (key)
	{
	case SKILL_Q:
		GET_OBJECT_LAYER->GetMyHero()->SetSkillCanUse(key, false);
		skillBlack = GET_UI_LAYER->GetQSkillBlack();
		skillBlack->setVisible(true);
		skillBlack->runAction(action);
		break;
	}
}

void ListenerLayer::CoolTimeEnd(SkillKey key)
{
	switch (key)
	{
	case SKILL_Q:
		GET_UI_LAYER->InvisibleSkillBlack(key);
		GET_OBJECT_LAYER->GetMyHero()->SetSkillCanUse(key, true);
		break;
	case SKILL_W:
		break;
	case SKILL_E:
		break;
	case SKILL_R:
		break;
	default:
		break;
	}
}

SkillKey ListenerLayer::KeyboardToSkillKey(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case KEY_Q:
		return SKILL_Q;
		break;
	case KEY_W:
		return SKILL_W;
		break;
	}
}
