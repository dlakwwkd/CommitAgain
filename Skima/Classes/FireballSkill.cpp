#include "pch.h"
#include "FireballSkill.h"


FireballSkill::FireballSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 1;

    CreateSprite("Images/Interface/fireball.jpg", Vec2(0.03f, 0.033f), Vec2(0.5, 0.5));
}


FireballSkill::~FireballSkill()
{
}