#include "stdafx.h"
#include "Magician.h"
#include "GameManager.h"
#include "FireballSkill.h"
#include "IceballSkill.h"
#include "TeleportSkill.h"
#include "BuffSkill.h"
#include "FireWallSkill.h"


Magician::Magician(Player* owner, const b2Vec2& pos, float scale)
{
    SetDynamicBody(owner, HERO_MAGICIAN, pos, scale);
    m_Hp = m_MaxHp = 1500;
    m_Speed = Reduce(320.0f);

    m_Buff = new BuffSkill(m_Owner);
    m_SkillList[SKILL_Q] = new FireballSkill(m_Owner, scale);
    m_SkillList[SKILL_W] = new IceballSkill(m_Owner, scale);
    m_SkillList[SKILL_E] = new TeleportSkill(m_Owner);
    m_SkillList[SKILL_R] = new FireWallSkill(m_Owner);
}


Magician::~Magician()
{
}