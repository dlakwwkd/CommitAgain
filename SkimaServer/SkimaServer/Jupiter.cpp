#include "stdafx.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "FlashSkill.h"

Jupiter::Jupiter(Player* owner, const b2Vec2& pos, float scale)
{
	SetDynamicBody(owner, HERO_JUPITER, pos, scale);
	m_Hp = m_MaxHp = 1000;
	m_Speed = REDUCE(500);

	m_SkillList[SKILL_Q] = new SparkSkill(m_Owner, scale);
    m_SkillList[SKILL_W] = new LightningSkill(m_Owner);
    m_SkillList[SKILL_E] = new FlashSkill(m_Owner);
}


Jupiter::~Jupiter()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
	for (auto& skill : m_SkillList)
	{
		delete skill.second;
	}
}