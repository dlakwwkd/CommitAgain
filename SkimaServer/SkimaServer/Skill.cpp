#include "stdafx.h"
#include "Skill.h"


Skill::Skill()
{
    m_TargetPos = { 0, 0 };
    m_Damage = 0;
    m_Range = 0.0f;
    m_HeroBodySize = 0.0f;
    m_IsOn = false;
}


Skill::~Skill()
{
}

