#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"
#include "PacketType.h"
#include <crtdbg.h>

#define COOLTIME_BOX_X 0.03f
#define COOLTIME_BOX_Y 0.033f

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    auto menuItem = MenuItemImage::create("Images/Interface/Exit.png","Images/Interface/Exit_selected.png", CC_CALLBACK_1(UILayer::ClickExit, this));
    menuItem->setScale(0.3f, 0.3f);
    auto menu = Menu::create(menuItem, NULL);
    auto hpLabel = Label::createWithSystemFont("\0","Thonburi",20);
    menu->setPosition(winSize.width - 40, 12);
    hpLabel->setPosition(Vec2(590, 105));
    this->addChild(menu);
    this->addChild(hpLabel, 11, "HpLabel");

    auto sprite = [](const char* image, Vec2 pos, Vec2 scale, Vec2 anchor)
    {
        auto sprite = Sprite::create(image);
        sprite->setPosition(pos);
        sprite->setScale(scale.x, scale.y);
        sprite->setAnchorPoint(anchor);
        return sprite;
    };
    this->addChild(sprite("Images/Interface/interface.png",       Vec2(400, 95), Vec2(1.03f, 1.030f), Vec2(0.5, 0.5)));
    this->addChild(sprite("Images/Interface/HpBar_interface.png", Vec2(400, 88), Vec2(0.68f, 1.030f), Vec2(0.0, 0.0)), 10, "HpBar");
    this->addChild(sprite("Images/Interface/fireball.jpg",        Vec2(443, 38), Vec2(0.03f, 0.033f), Vec2(0.5, 0.5)));
    this->addChild(sprite("Images/Interface/iceball.jpg",         Vec2(518, 38), Vec2(0.55f, 0.800f), Vec2(0.5, 0.5)));
    this->addChild(sprite("Images/Interface/teleport_icon.png",   Vec2(590, 38), Vec2(0.70f, 0.800f), Vec2(0.5, 0.5)));
    this->addChild(sprite("Images/Interface/Meteor_icon.png",     Vec2(663, 38), Vec2(0.55f, 0.800f), Vec2(0.5, 0.5)));

    auto cooltimeBox = [&](SkillKey key, Vec2 pos)
    {
        m_CooltimeBox[key] = sprite("Images/Interface/black.jpg", pos, Vec2(COOLTIME_BOX_X, COOLTIME_BOX_Y), Vec2(0.0, 0.0));
        m_CooltimeBox[key]->setOpacity(200);
        return m_CooltimeBox[key];
    };
    this->addChild(cooltimeBox(SKILL_Q, Vec2(413, 8)));
    this->addChild(cooltimeBox(SKILL_W, Vec2(490, 8)));
    this->addChild(cooltimeBox(SKILL_E, Vec2(567, 8)));
    this->addChild(cooltimeBox(SKILL_R, Vec2(630, 8)));
    
	auto cursor = [&](CursorMode mode, const char* image, Vec2 scale, Vec2 anchor)
    {
		m_CursorShape[mode] = sprite(image, Vec2::ZERO, scale, anchor);
        m_CursorShape[mode]->setVisible(false);
        return m_CursorShape[mode];
    };
	m_Cursor = cursor(CURSOR_DEFAULT, "Images/Cursor/cursor_default.png", Vec2(1, 1), Vec2(0, 1));
    m_Cursor->setVisible(true);
    this->addChild(m_Cursor, 10);
	this->addChild(cursor(CURSOR_ATTACK, "Images/Cursor/cursor_attack.png",			Vec2(1, 1),			Vec2(0, 1)),		10);
	this->addChild(cursor(CURSOR_TELEPORT, "Images/Cursor/cursor_teleport.png",		Vec2(0.2f, 0.08f),	Vec2(0.5f, 0.5f)),	10);
	this->addChild(cursor(CURSOR_SPLASH, "Images/Cursor/cursor_splash.png",			Vec2(1.5f, 1.5f),	Vec2(0.5f, 0.5f)),	10);

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
	ShowCursor(true);
	TcpClient::getInstance()->disconnect();
    Director::getInstance()->popScene();
}

void UILayer::UpdateHpBar(float curHp, float maxHp)
{
    char* currentHp = (char*)calloc(255,sizeof(char));
    char* maximumHp = (char*)calloc(255, sizeof(char));
    itoa(curHp, currentHp, 10); itoa(maxHp, maximumHp, 10);
    strcat(currentHp, " / "); strcat(currentHp, maximumHp);
    auto hpLabel = dynamic_cast<Label*>(this->getChildByName("HpLabel"));
    hpLabel->setString(currentHp);
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
