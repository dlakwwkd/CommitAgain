#include "pch.h"
#include "Skill.h"
#include "Hero.h"


Skill::Skill()
{
    m_Hero = nullptr;
    m_CoolTime = 0;
    m_CanUse = false;
}

Skill::Skill(Hero* hero) :m_Hero(hero)
{
    m_CoolTime = 0;
    m_CanUse = false;
}


Skill::~Skill()
{
}
