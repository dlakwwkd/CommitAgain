#include "pch.h"
#include "Buff.h"
#include "Hero.h"


Buff::Buff()
{
}


Buff::~Buff()
{
}

void Buff::SkillCast(Vec2 heroPos, Vec2 targetPos)
{

}

void Buff::SkillReady()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(true);
}

void Buff::SkillEnd()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(false);
}

void Buff::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
