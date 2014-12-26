#include "pch.h"
#include "SparkSkill.h"


SparkSkill::SparkSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
}

SparkSkill::~SparkSkill()
{
}
