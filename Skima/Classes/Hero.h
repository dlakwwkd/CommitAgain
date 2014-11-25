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
	bool		GetSkillCanUse(SkillKey key);

	void		SetSkillCanUse(SkillKey key, bool isUse);

protected:
	HeroType					m_HeroType;
	std::map<SkillKey, Skill*>	m_SkillList;
};

