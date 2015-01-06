#include "stdafx.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "FlashSkill.h"
#include "BuffSkill.h"
#include "LightningPumpkinSkill.h"


Jupiter::Jupiter(Player* owner, const b2Vec2& pos, float scale)
{
	SetDynamicBody(owner, HERO_JUPITER, pos, scale);
	m_Hp = m_MaxHp = 1800;
	m_Speed = Reduce(370.0f);

    m_Buff = new BuffSkill(m_Owner);
	m_SkillList[SKILL_Q] = new SparkSkill(m_Owner, scale);
    m_SkillList[SKILL_W] = new LightningSkill(m_Owner);
    m_SkillList[SKILL_E] = new FlashSkill(m_Owner);
    m_SkillList[SKILL_R] = new LightningPumpkinSkill(m_Owner);
}


Jupiter::~Jupiter()
{
}