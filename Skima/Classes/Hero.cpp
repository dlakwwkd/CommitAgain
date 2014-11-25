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

bool Hero::GetSkillCanUse(SkillKey key)
{
	return m_SkillList[key]->GetCanUse();
}

void Hero::SetSkillCanUse(SkillKey key, bool isUse)
{
	m_SkillList[key]->SetCanUse(isUse);
}
