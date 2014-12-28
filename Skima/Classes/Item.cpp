#include "pch.h"
#include "Item.h"
#include "GameManager.h"
#include "ObjectLayer.h"


Item::Item(Vec2 createPos, float scale)
{
    m_UnitType = UNIT_MOB;
    m_MaxHp = 200.0f;
    m_CurHp = m_MaxHp;
    m_Speed = 100.0f;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    m_RealSprite = Sprite::create("Images/Pea.png");
    m_RealSprite->setScale(scale);
    m_RealSprite->setAnchorPoint(Vec2(0, 0));
    m_CenterSprite->addChild(m_RealSprite);
}


Item::~Item()
{
}
