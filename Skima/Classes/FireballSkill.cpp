#include "pch.h"
#include "FireballSkill.h"
#include "GameManager.h"
#include "Missile.h"
#include "Hero.h"


FireballSkill::FireballSkill()
{
    m_SkillType = MISSILE_SKILL;
    m_CoolTime = 3;
    m_CanUse = true;
}

FireballSkill::FireballSkill(Hero* hero)
{
    m_SkillType = MISSILE_SKILL;
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


FireballSkill::~FireballSkill()
{
}
// 
// void FireballSkill::SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID)
// {
// 	auto missile = static_cast<Missile*>(GET_MM->Assign(UNIT_MISSILE));
// 	missile->MissileCast(heroPos, targetPos);
// }

void FireballSkill::SkillReady()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(true);
}

void FireballSkill::SkillEnd()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(false);
}

