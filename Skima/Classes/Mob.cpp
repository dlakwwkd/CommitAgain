#include "pch.h"
#include "Mob.h"
#include "GameManager.h"
#include "ObjectLayer.h"


Mob::Mob(Vec2 createPos, float scale, int hp, float speed)
{
    m_UnitType = UNIT_MOB;
    m_MaxHp = hp;
    m_CurHp = m_MaxHp;
    m_Speed = speed;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    m_RealSprite = Sprite::create("Images/Unit/Pea.png");
    m_RealSprite->setScale(scale);
    m_CenterSprite->addChild(m_RealSprite);
}


Mob::~Mob()
{
}
