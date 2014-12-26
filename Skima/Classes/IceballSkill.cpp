#include "pch.h"
#include "IceballSkill.h"


IceballSkill::IceballSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 1;
}

IceballSkill::~IceballSkill()
{
}