#include "pch.h"
#include "ShootType.h"
#include "Hero.h"


ShootType::ShootType()
{
}


ShootType::~ShootType()
{
}

void ShootType::SkillCast(Vec2 heroPos, Vec2 targetPos)
{

}

void ShootType::SkillReady()
{
    auto arrow = m_Owner->GetArrow();
    arrow->setVisible(true);
}

void ShootType::SkillEnd()
{
    auto arrow = m_Owner->GetArrow();
    arrow->setVisible(false);
}

void ShootType::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
