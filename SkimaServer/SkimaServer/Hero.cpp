#include "stdafx.h"
#include "Hero.h"
#include "Skill.h"

Hero::Hero()
{
    m_UnitID = SET_MAIN_TYPE(m_UnitID, UNIT_HERO);
}

Hero::~Hero()
{
}

void Hero::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto skill = m_SkillList.find(skillKey);
    if (skill == m_SkillList.end())
    {
        printf("UseSkill() Failed!! \n");
        return;
    }
    skill->second->SkillCast(heroPos, targetPos);
}
