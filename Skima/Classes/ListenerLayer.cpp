#include "pch.h"
#include "ListenerLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Skill.h"
#include "PacketType.h"
#include "Hero.h"
#include "UILayer.h"
#include "EscLayer.h"
#include "math.h"

#define GET_OBJECT_LAYER    dynamic_cast<ObjectLayer*>(this->getChildByName(OBJECT_LAYER))
#define GET_UI_LAYER        dynamic_cast<UILayer*>(this->getParent()->getChildByName(UI_LAYER))
#define GET_ESC_LAYER       dynamic_cast<EscLayer*>(this->getParent()->getChildByName(ESC_LAYER))

bool ListenerLayer::init()
{
    
    if (!Layer::init())
    {
        return false;
    }
    //this->setPosition(-(MAX_MAP_SIZE_X - DISPLAY_X)/2, -(MAX_MAP_SIZE_Y - DISPLAY_Y)/2);

    auto layer1 = MapLayer::create();
    auto layer2 = ObjectLayer::create();
    this->addChild(layer1, 0, MAP_LAYER);
    this->addChild(layer2, 1, OBJECT_LAYER);

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

	layer2->schedule(schedule_selector(ObjectLayer::Tick));
    return true;
}


///////////////////////////////////////////////////////////////////////////
/*
    마우스 리스너
*/
///////////////////////////////////////////////////////////////////////////
void ListenerLayer::OnMouseDown(Event *event)
{
    if (!dynamic_cast<GameScene*>(this->getParent())->IsStartGame())
    {
        return;
    }
    auto hero = GET_OBJECT_LAYER->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    auto sprite = hero->GetCenterSprite();				_ASSERT(sprite != nullptr);
    auto heroPos = sprite->getPosition();
    auto mousePos = GET_IM->GetMouseLocation();
    auto key = KeyboardToSkillKey(GET_IM->SearchTargetingKey());
    auto button = static_cast<EventMouse*>(event)->getMouseButton();
    GET_IM->SetMouseStatus(button, true);

    switch (button)
    {
    case MOUSE_BUTTON_LEFT:
        {
            if (!m_Targeting || key == SKILL_NONE)
            {
                break;
            }
			TcpClient::getInstance()->skillRequest(heroPos, mousePos - this->getPosition(), key);
            CoolTimeStart(key);

            hero->SkillEnd(key);
            GET_UI_LAYER->CursorChange(CURSOR_DEFAULT);
            GET_UI_LAYER->GetCurrentCursor()->setPosition(mousePos);
            GET_IM->InitTargetingKey();
            m_Targeting = false;
        }
        break;

    case MOUSE_BUTTON_RIGHT:
        {
            if (hero->GetMoveState() != hero->GetCrashedState())
            {
    			TcpClient::getInstance()->moveRequest(heroPos, mousePos - this->getPosition());
            }
            if (key != SKILL_NONE)
            {
                hero->SkillEnd(key);
                GET_UI_LAYER->CursorChange(CURSOR_DEFAULT);
                GET_UI_LAYER->GetCurrentCursor()->setPosition(mousePos);
                GET_IM->InitTargetingKey();
                m_Targeting = false;
            }
        }
        break;
    }
}

void ListenerLayer::OnMouseUp(Event *event)
{
    auto button = static_cast<EventMouse*>(event)->getMouseButton();
    GET_IM->SetMouseStatus(button, false);
}

void ListenerLayer::OnMouseMove(Event *event)
{
    auto location = static_cast<EventMouse*>(event)->getLocation();
    location.y = Director::getInstance()->getWinSize().height - location.y;

    GET_IM->SetMouseLocation(location);
    GET_UI_LAYER->GetCurrentCursor()->setPosition(location);

    auto hero = GET_OBJECT_LAYER->GetMyHero();
    if (hero == nullptr)
        return;

    SetArrowPos(hero->GetArrow(), 100);
    SetArrowPos(hero->GetNearSkillRange(), 120);
}



///////////////////////////////////////////////////////////////////////////
/*
    키보드 리스너
*/
///////////////////////////////////////////////////////////////////////////
void ListenerLayer::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    GET_IM->SetKeyStatus(keyCode, true);

    auto key = KeyboardToSkillKey(keyCode);
    if (key == SKILL_NONE)
    {
        switch (keyCode)
        {
        case KEY_ESC:
            {
                GET_ESC_LAYER->ShowEscLayer();
            }
            break;
        }
    }

    auto hero = GET_OBJECT_LAYER->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    if (!m_Targeting && hero->GetSkillCanUse(key))
    {
        GET_UI_LAYER->CursorChange(CURSOR_ATTACK);
        GET_UI_LAYER->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());
        GET_IM->SetTargeting(keyCode, true);
        hero->SkillReady(key);
        m_Targeting = true;
    }
}

void ListenerLayer::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    GET_IM->SetKeyStatus(keyCode, false);
}



///////////////////////////////////////////////////////////////////////////
/*
    private 함수들
*/
///////////////////////////////////////////////////////////////////////////
SkillKey ListenerLayer::KeyboardToSkillKey(EventKeyboard::KeyCode keyCode)
{
    switch (keyCode)
    {
    case KEY_Q: return SKILL_Q;
    case KEY_W: return SKILL_W;
    case KEY_E: return SKILL_E;
    case KEY_R: return SKILL_R;
    default:    return SKILL_NONE;
    }
}

void ListenerLayer::CoolTimeStart(SkillKey key)
{
    auto reduceWidth = ScaleBy::create(GET_OBJECT_LAYER->GetMyHero()->GetSkillCoolTime(key), 0.0f, 1.0f);
    auto coolTimeEnd = CallFunc::create(CC_CALLBACK_0(ListenerLayer::CoolTimeEnd, this, key));
    auto action = Sequence::create(reduceWidth, coolTimeEnd, NULL);

    auto cooltimeBox = GET_UI_LAYER->GetCooltimeBox(key);
    cooltimeBox->setVisible(true);
    cooltimeBox->runAction(action);

    GET_OBJECT_LAYER->GetMyHero()->SetSkillCanUse(key, false);
}

void ListenerLayer::CoolTimeEnd(SkillKey key)
{
    GET_UI_LAYER->HideCooltimeBox(key);
    GET_OBJECT_LAYER->GetMyHero()->SetSkillCanUse(key, true);
}

void ListenerLayer::SetArrowPos(Sprite* arrow, float posGap)
{
    if (!m_Targeting || GET_OBJECT_LAYER->GetMyHero() == nullptr)
    {
        return;
    }
    auto hero = GET_OBJECT_LAYER->GetMyHero();
    auto displacement = GET_IM->GetMouseLocation() - this->getPosition() - hero->GetHeroPos();
    auto distance = displacement.getLength();

    float degree = acos(displacement.y / distance) / M_PI * 180; //내적
    if (displacement.x < 0)
    {
        degree = degree * -1;
    }
    arrow->setPosition(displacement / distance * posGap);
    arrow->setRotation(degree);
}
