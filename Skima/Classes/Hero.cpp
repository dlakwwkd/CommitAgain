#include "pch.h"
#include "Hero.h"
#include "Skill.h"


Hero::Hero()
{
}


Hero::~Hero()
{
	for (auto& skill : m_SkillList)
	{
		delete skill.second;
	}
}
