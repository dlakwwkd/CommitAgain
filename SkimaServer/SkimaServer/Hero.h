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
    void				UseSkill(SkillKey skillKey, const b2Vec2& heroPos, const b2Vec2& targetPos);
    void                StopSkill();

protected:
    SkillList	        m_SkillList;
};

