#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"
#include "PacketType.h"

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->schedule(schedule_selector(UILayer::Tick));

	auto menuItem1 = MenuItemImage::create(	"Images/Exit.png","Images/Exit_selected.png",
		CC_CALLBACK_1(UILayer::ClickExit, this));
	menuItem1->setScale(0.3f, 0.3f);

	auto interfaceimage = Sprite::create("Images/interface.jpg");
	interfaceimage->setPosition(Point(400, 95));
	interfaceimage->setScale(1.03f, 1.03f);
	this->addChild(interfaceimage);

	auto fireball = Sprite::create("Images/fireball.jpg");
	fireball->setPosition(Point(443, 38));
	fireball->setScale(0.03f, 0.033f);
	this->addChild(fireball);
	
	m_Q_Skill_black = Sprite::create("Images/black.jpg");
	m_Q_Skill_black->setPosition(Point(443, 38));
	m_Q_Skill_black->setScale(0.03f, 0.033f);
	m_Q_Skill_black->setOpacity(180);
	this->addChild(m_Q_Skill_black);

	auto winSize = Director::getInstance()->getWinSize();
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(winSize.width -40 , 12);
	this->addChild(menu);

	m_CursorDefault = Sprite::create("Images/mouse_cursor.jpg");
	m_CursorAttack = Sprite::create("Images/attack_cursor.jpg");
	m_CursorDefault->setAnchorPoint(Point(0, 0.9f));
	m_CursorAttack->setAnchorPoint(Point(0, 0.9f));
	this->addChild(m_CursorDefault);
	this->addChild(m_CursorAttack);
	m_CursorAttack->setVisible(false);
	m_CursorShape = m_CursorDefault;

	return true;
}

void UILayer::Tick(float dt)
{
	if (m_Q_Skill_On)
	{
	}
}

void UILayer::CursorChange(CursorMode cursorMode)
{
	switch (cursorMode)
	{
	case CURSOR_DEFAULT:
		m_CursorAttack->setVisible(false);
		m_CursorDefault->setVisible(true);
		m_CursorShape = m_CursorDefault;
		break;
	case CURSOR_ATTACK:
		m_CursorAttack->setVisible(true);
		m_CursorDefault->setVisible(false);
		m_CursorShape = m_CursorAttack;
		break;
	}
}

void UILayer::SetSkillUse(SkillKey key, bool skillOn)
{
	switch (key)
	{
	case SKILL_Q:
		m_Q_Skill_On = skillOn;
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

void UILayer::ClickExit(Ref* sender)
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
	ShowCursor(true);
}