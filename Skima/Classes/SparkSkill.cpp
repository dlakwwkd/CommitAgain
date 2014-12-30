#include "pch.h"
#include "SparkSkill.h"


SparkSkill::SparkSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    CreateSprite("Images/Interface/spark.jpg", Vec2(0.077f, 0.11f), Vec2(0.5, 0.5));
}

SparkSkill::~SparkSkill()
{
}
