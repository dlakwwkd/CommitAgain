#include "pch.h"
#include "FireballSkill.h"


FireballSkill::FireballSkill()
{
    m_CoolTime = 3;
}

FireballSkill::FireballSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
}


FireballSkill::~FireballSkill()
{
}