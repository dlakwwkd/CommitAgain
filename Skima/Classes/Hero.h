#pragma once
#include "Unit.h"

class Skill;

class Hero :
	public Unit
{
public:
	Hero();
	~Hero();

	HeroType GetHeroType(){ return m_HeroType; }

protected:
	HeroType					m_HeroType;
	std::map<SkillKey, Skill*>	m_SkillList;
};

