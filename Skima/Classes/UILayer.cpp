#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"

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
	
	m_Q_SKill_black = Sprite::create("Images/black.jpg");
	m_Q_SKill_black->setPosition(Point(443, 38));
	m_Q_SKill_black->setScale(0.03f, 0.033f);
	m_Q_SKill_black->setOpacity(180);
	this->addChild(m_Q_SKill_black);

	auto winSize = Director::getInstance()->getWinSize();
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(winSize.width -40 , 12);
	this->addChild(menu);

	m_cursor_default = Sprite::create("Images/mouse_cursor.jpg");
	m_cursor_attack = Sprite::create("Images/attack_cursor.jpg");
	m_cursor_default->setAnchorPoint(Point(0, 1.5));
	m_cursor_attack->setAnchorPoint(Point(0, 1.5));
	this->addChild(m_cursor_default);
	this->addChild(m_cursor_attack);
	m_cursor_attack->setVisible(false);
	m_cursor_shape = m_cursor_default;

	return true;
}

void UILayer::ClickExit(Ref* sender)
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
}

void UILayer::CursorChange(CursorMode cursormode)
{
	switch (cursormode)
	{
	case CURSOR_DEFAULT:
		m_cursor_attack->setVisible(false);
		m_cursor_default->setVisible(true);
		m_cursor_shape = m_cursor_default;
		break;
	case CURSOR_ATTACK:
		m_cursor_attack->setVisible(true);
		m_cursor_default->setVisible(false);
		m_cursor_shape = m_cursor_attack;
		break;
	}
}

void UILayer::Tick(float dt)
{
	//
}
