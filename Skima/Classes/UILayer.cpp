#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"
#include "PacketType.h"
#include <crtdbg.h>

bool UILayer::init()
{
    if (!Layer::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();

    auto menuItem = MenuItemImage::create(
        "Images/Interface/Exit.png",
        "Images/Interface/Exit_selected.png",
        CC_CALLBACK_1(UILayer::ClickExit, this));
    menuItem->setScale(0.3f, 0.3f);

    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(winSize.width - 40, 12);
    this->addChild(menu);

    auto hpLabel = Label::createWithSystemFont("\0", DEF_FONT, 23);
    hpLabel->setPosition(Vec2(MAX_MAP_SIZE_X / 2, 143));
    this->addChild(hpLabel, 11, HP_LABEL);

    this->addChild(MakeSprite("Images/Interface/interface.png",         Vec2(MAX_MAP_SIZE_X / 2, 100),          Vec2(1.1f, 1.1f),   Vec2(0.5, 0.5)));
    this->addChild(MakeSprite("Images/Interface/HpBar_interface.png",   Vec2(MAX_MAP_SIZE_X / 2 - 204, 141),    Vec2(0.72f, 1.1f),  Vec2(0.0, 0.5)),    10, HP_BAR);

    this->addChild(MakeCooltimeBox(SKILL_Q, Vec2(MAX_MAP_SIZE_X / 2 - 150, 48)));
    this->addChild(MakeCooltimeBox(SKILL_W, Vec2(MAX_MAP_SIZE_X / 2 - 70, 48)));
    this->addChild(MakeCooltimeBox(SKILL_E, Vec2(MAX_MAP_SIZE_X / 2 + 13, 48)));
    this->addChild(MakeCooltimeBox(SKILL_R, Vec2(MAX_MAP_SIZE_X / 2 + 92, 48)));
    
    m_Cursor = MakeCursor(CURSOR_DEFAULT, "Images/Cursor/cursor_default.png", Vec2(1, 1), Vec2(0, 1));
    m_Cursor->setVisible(true);
    this->addChild(m_Cursor, 10);
    this->addChild(MakeCursor(CURSOR_ATTACK, "Images/Cursor/cursor_attack.png",     Vec2(1, 1),         Vec2(0, 1)),        10);
    this->addChild(MakeCursor(CURSOR_TELEPORT, "Images/Cursor/cursor_teleport.png", Vec2(0.2f, 0.08f),  Vec2(0.5f, 0.5f)),  10);
    this->addChild(MakeCursor(CURSOR_SPLASH, "Images/Cursor/cursor_splash.png",     Vec2(1.5f, 1.5f),   Vec2(0.5f, 0.5f)),  10);
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
    m_CooltimeBox[key]->setScale(0.5, 0.5);
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
    auto hpLabel = dynamic_cast<Label*>(this->getChildByName(HP_LABEL));
    hpLabel->setString(currentHp);
    auto hpBar = dynamic_cast<Sprite*>(this->getChildByName(HP_BAR));
    hpBar->setScaleX(0.72f*(curHp / maxHp));
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



Sprite* UILayer::MakeSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor)
{
    auto sprite = Sprite::create(image);
    sprite->setPosition(pos);
    sprite->setScale(scale.x, scale.y);
    sprite->setAnchorPoint(anchor);
    return sprite;
}

Sprite* UILayer::MakeCooltimeBox(SkillKey key, Vec2 pos)
{
    m_CooltimeBox[key] = MakeSprite("Images/Interface/black.jpg", pos, Vec2(0.5, 0.5), Vec2(0.0, 0.0));
    m_CooltimeBox[key]->setOpacity(200);
    m_CooltimeBox[key]->setZOrder(10);
    return m_CooltimeBox[key];
}

Sprite* UILayer::MakeCursor(CursorMode mode, const char* image, Vec2 scale, Vec2 anchor)
{
    m_CursorShape[mode] = MakeSprite(image, Vec2::ZERO, scale, anchor);
    m_CursorShape[mode]->setVisible(false);
    return m_CursorShape[mode];
}
