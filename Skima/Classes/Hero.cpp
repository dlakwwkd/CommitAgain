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

int Hero::GetSkillCoolTime(SkillKey key)
{
	return m_SkillList[key]->GetCoolTime();
}
