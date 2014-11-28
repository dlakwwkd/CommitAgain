#include "pch.h"
#include "Hero.h"
#include "Skill.h"


Hero::Hero()
{
	m_Arrow = Sprite::create("Images/arrow.png");
	m_Arrow->setScale(0.09f, 0.09f);
	m_Arrow->setPosition(Vec2(50, 50));
	m_Arrow->setVisible(false);
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
	auto skill = m_SkillList.find(key);
	if (skill == m_SkillList.end())
	{
		return 1;
	}
	return skill->second->GetCoolTime();
}

bool Hero::GetSkillCanUse(SkillKey key)
{
	auto skill = m_SkillList.find(key);
	if (skill == m_SkillList.end())
	{
		return false;
	}
	return skill->second->GetCanUse();
}

void Hero::SetSkillCanUse(SkillKey key, bool isUse)
{
	auto skill = m_SkillList.find(key);
	if (skill == m_SkillList.end())
	{
		return;
	}
	skill->second->SetCanUse(isUse);
}

void Hero::SkillReady(SkillKey key)
{
	auto skill = m_SkillList.find(key);
	if (skill == m_SkillList.end())
	{
		return;
	}
	skill->second->SkillReady();
}

void Hero::SkillEnd(SkillKey key)
{
	auto skill = m_SkillList.find(key);
	if (skill == m_SkillList.end())
	{
		return;
	}
	skill->second->SkillEnd();
}
