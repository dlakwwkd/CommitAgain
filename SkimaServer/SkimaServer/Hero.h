#pragma once
#include "Unit.h"
class Skill;

typedef std::map<SkillKey, Skill*> SkillList;

class Hero : public Unit
{
public:
    Hero();
    virtual ~Hero();

    const SkillList&	GetSkillList(){ return m_SkillList; }

    virtual void UseSkill(SkillType skillType, SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
    virtual void        Extinction(){}

protected:
    SkillList	m_SkillList;
};

