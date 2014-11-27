#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"
#include "PacketType.h"

#define COOLTIME_BOX_X 0.03f
#define COOLTIME_BOX_Y 0.033f

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	auto menuItem = MenuItemImage::create("Images/Exit.png","Images/Exit_selected.png", CC_CALLBACK_1(UILayer::ClickExit, this));
	menuItem->setScale(0.3f, 0.3f);
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(winSize.width - 40, 12);
	this->addChild(menu);


	auto sprite = [](const char* image, Point pos, Point scale, Point anchor)
	{
		auto sprite = Sprite::create(image);
		sprite->setPosition(pos);
		sprite->setScale(scale.x, scale.y);
		sprite->setAnchorPoint(anchor);
		return sprite;
	};
	this->addChild(sprite("Images/interface.png",		Point(400, 95), Point(1.03f, 1.030f), Point(0.5, 0.5)));
	this->addChild(sprite("Images/HpBar_interface.png", Point(400, 88), Point(0.68f, 1.030f), Point(0.0, 0.0)), 10, "HpBar");
	this->addChild(sprite("Images/fireball.jpg",			Point(443, 38), Point(0.03f, 0.033f), Point(0.5, 0.5)));
	this->addChild(sprite("Images/iceball.jpg",			Point(518, 38), Point(0.55f, 0.800f), Point(0.5, 0.5)));
	

	auto cooltimeBox = [&](SkillKey key, Point pos)
	{
		m_CooltimeBox[key] = sprite("Images/black.jpg", pos, Point(COOLTIME_BOX_X, COOLTIME_BOX_Y), Point(0.0, 0.0));
		m_CooltimeBox[key]->setOpacity(200);
		return m_CooltimeBox[key];
	};
	this->addChild(cooltimeBox(SKILL_Q, Point(413, 8)));
	this->addChild(cooltimeBox(SKILL_W, Point(490, 8)));

	
	auto cursor = [&](CursorMode mode, const char* image, Point scale)
	{
		m_CursorShape[mode] = sprite(image, Point::ZERO, scale, Point(0, 1));
		m_CursorShape[mode]->setVisible(false);
		return m_CursorShape[mode];
	};
	m_Cursor = cursor(CURSOR_DEFAULT, "Images/cursor_defualt.png", Point(1, 1));
	m_Cursor->setVisible(true);
	this->addChild(m_Cursor, 10);
	this->addChild(cursor(CURSOR_ATTACK,		"Images/cursor_attack.png",		Point(1, 1)),		 10);
	this->addChild(cursor(CURSOR_TELEPORT,	"Images/cursor_teleport.png",	Point(0.2f, 0.08f)), 10);

	return true;
}

void UILayer::CursorChange(CursorMode mode)
{
	auto sprite = m_CursorShape.find(mode);
	if (sprite == m_CursorShape.end())
	{
		return;
	}
	for (auto& shape : m_CursorShape)
	{
		shape.second->setVisible(false);
	}
	m_CursorShape[mode]->setVisible(true);
	m_Cursor = m_CursorShape[mode];
}

void UILayer::HideCooltimeBox(SkillKey key)
{
	auto sprite = m_CooltimeBox.find(key);
	if (sprite == m_CooltimeBox.end())
	{
		return;
	}
	m_CooltimeBox[key]->setVisible(false);
	m_CooltimeBox[key]->setScale(COOLTIME_BOX_X, COOLTIME_BOX_Y);
}

void UILayer::ClickExit(Ref* sender)
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
	ShowCursor(true);
}

void UILayer::UpdateHpBar(float curHp, float maxHp)
{
	auto hpBar = dynamic_cast<Sprite*>(this->getChildByName("HpBar"));
	hpBar->setScaleX(0.68f*(curHp / maxHp));
}

Sprite* UILayer::GetCooltimeBox(SkillKey key)
{
	auto sprite = m_CooltimeBox.find(key);
	if (sprite == m_CooltimeBox.end())
	{
		return nullptr;
	}
	return m_CooltimeBox[key];
}
