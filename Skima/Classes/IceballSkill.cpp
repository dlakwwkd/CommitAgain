#include "pch.h"
#include "IceballSkill.h"


IceballSkill::IceballSkill()
{
    m_CoolTime = 3;
}

IceballSkill::IceballSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
}

IceballSkill::~IceballSkill()
{
}