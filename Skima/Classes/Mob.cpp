#include "pch.h"
#include "Mob.h"
#include "GameManager.h"
#include "ObjectLayer.h"


Mob::Mob(Vec2 createPos, float scale)
{
    m_UnitType = UNIT_MOB;
    m_MaxHp = 200.0f;
    m_CurHp = m_MaxHp;
    m_Speed = 100.0f;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    m_RealSprite = Sprite::create("Images/Unit/Pea.png");
    m_RealSprite->setScale(scale);
    m_RealSprite->setAnchorPoint(Vec2(0, 0));
    m_CenterSprite->addChild(m_RealSprite);
}


Mob::~Mob()
{
}
