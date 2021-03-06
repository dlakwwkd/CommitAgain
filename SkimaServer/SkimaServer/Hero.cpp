﻿#include "stdafx.h"
#include "Hero.h"
#include "Skill.h"


Hero::Hero()
{
    m_UnitID = SET_MAIN_TYPE(MakeID(this), UNIT_HERO);
    m_IsHidden = false;
}

Hero::~Hero()
{
    for (auto& skill : m_SkillList)
    {
        delete skill.second;
    }
}

void Hero::UseSkill(SkillKey skillKey, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto skill = m_SkillList.find(skillKey);
    if (skill == m_SkillList.end())
    {
        printf("UseSkill() Failed!! \n");
        return;
    }
    skill->second->SkillCast(skillKey, heroPos, targetPos);
}

void Hero::StopSkill()
{
    for (auto& skill : m_SkillList)
    {
        skill.second->CastStop();
    }
}
