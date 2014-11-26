#include "pch.h"
#include "Hero.h"
#include "Skill.h"


Hero::Hero()
{
	m_Arrow = Sprite::create("Images/arrow.png");
	m_Arrow->setScale(0.09f, 0.09f);
	m_Arrow->setPosition(Point(50, 50));
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

void Hero::SkillReady(SkillKey key)
{
	m_SkillList[key]->SkillReady();
}

void Hero::SkillEnd(SkillKey key)
{
	m_SkillList[key]->SkillEnd();

}
