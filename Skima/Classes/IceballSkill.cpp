#include "pch.h"
#include "IceballSkill.h"


IceballSkill::IceballSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 1;
}

IceballSkill::~IceballSkill()
{
}