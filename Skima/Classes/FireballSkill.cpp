#include "pch.h"
#include "FireballSkill.h"


FireballSkill::FireballSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 1;
}


FireballSkill::~FireballSkill()
{
}