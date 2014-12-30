#include "pch.h"
#include "IceballSkill.h"


IceballSkill::IceballSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 2;

    CreateSprite("Images/Interface/iceball.jpg");
}

IceballSkill::~IceballSkill()
{
}