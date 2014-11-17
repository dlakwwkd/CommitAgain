#include "pch.h"
#include "Hero.h"


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
