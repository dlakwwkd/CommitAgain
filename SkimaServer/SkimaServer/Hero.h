#pragma once
#include "Unit.h"
class Skill;

typedef std::map<SkillKey, Skill*> SkillList;

class Hero : public Unit
{
public:
	Hero();
	virtual ~Hero();

	HeroType			GetHeroType(){ return m_HeroType; }
	const SkillList&	GetSkillList(){ return m_SkillList; }

    virtual void		UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
    virtual void        Extinction(){}

protected:
	HeroType    m_HeroType;
	SkillList	m_SkillList;
};

