#pragma once
#include "Unit.h"
class Skill;

typedef std::map<SkillKey, Skill*> SkillList; ///# 스킬 개수가 정해져 있다면 이렇게 맵을 쓸 이유가 없다. 그냥 고정 크기 배열 ㄱㄱ

class Hero : public Unit
{
public:
    Hero();
    virtual ~Hero();

    const SkillList&	GetSkillList(){ return m_SkillList; }

    virtual void		UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
    virtual void        Extinction(){}

protected:
    SkillList	m_SkillList;
};

