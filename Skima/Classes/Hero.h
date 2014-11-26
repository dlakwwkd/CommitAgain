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
	Point		GetHeroPos() { return m_Sprite->getPosition(); }
	Sprite*		GetArrow() { return m_Arrow; }

	void		SetSkillCanUse(SkillKey key, bool isUse);

	void		SkillReady(SkillKey key);
	void		SkillEnd(SkillKey key);

protected:
	HeroType					m_HeroType;
	std::map<SkillKey, Skill*>	m_SkillList;

	Sprite*						m_Arrow;
};

