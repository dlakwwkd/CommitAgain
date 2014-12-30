#include "pch.h"
#include "FireballSkill.h"


FireballSkill::FireballSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 2;

    CreateSprite("Images/Interface/fireball.jpg");
}


FireballSkill::~FireballSkill()
{
}