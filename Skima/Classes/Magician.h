#pragma once
#include "Hero.h"
#include "FireballSkill.h"
class Magician :
	public Hero
{
public:
	Magician(Point createPos, float scale);
	~Magician();

private:
	std::map<SkillKey, Skill*> m_SkillList;
};

