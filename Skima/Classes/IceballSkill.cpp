#include "pch.h"
#include "IceballSkill.h"


IceballSkill::IceballSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 1;

    CreateSprite("Images/Interface/iceball.jpg", Vec2(0.55f, 0.800f), Vec2(0.5, 0.5));
}

IceballSkill::~IceballSkill()
{
}