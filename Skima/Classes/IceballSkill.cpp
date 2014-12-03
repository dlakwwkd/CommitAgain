#include "pch.h"
#include "IceballSkill.h"
#include "GameManager.h"
#include "Missile.h"
#include "Hero.h"


IceballSkill::IceballSkill()
{
    m_SkillType = MISSILE_SKILL;
    m_CoolTime = 3;
    m_CanUse = true;
}

IceballSkill::IceballSkill(Hero* hero)
{
    m_SkillType = MISSILE_SKILL;
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}

IceballSkill::~IceballSkill()
{
}
// 
// void IceballSkill::SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID)
// {
// 	auto missile = static_cast<Missile*>(GET_MM->Assign(UNIT_MISSILE));
// 	missile->MissileCast(heroPos, targetPos);
// }

void IceballSkill::SkillReady()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(true);
}

void IceballSkill::SkillEnd()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(false);
}
