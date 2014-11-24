#pragma once
#include "Unit.h"

class Skill;

class Hero :
	public Unit
{
public:
	Hero();
	virtual ~Hero();

	HeroType	GetHeroType(){ return m_HeroType; }
	int			GetSkillCoolTime(SkillKey key);

protected:
	HeroType					m_HeroType;
	std::map<SkillKey, Skill*>	m_SkillList;
};

