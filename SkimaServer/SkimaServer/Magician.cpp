#include "stdafx.h"
#include "Magician.h"
#include "GameManager.h"
#include "FireballSkill.h"
#include "IceballSkill.h"
#include "TeleportSkill.h"


Magician::Magician(Player* owner, const b2Vec2& pos, float scale)
{
	SetDynamicBody(owner, HERO_MAGICIAN, pos, scale);
    m_Hp = m_MaxHp = 1000;
    m_Speed = REDUCE(360);
    
    m_SkillList[SKILL_Q] = new FireballSkill(m_Owner, scale);
	m_SkillList[SKILL_W] = new IceballSkill(m_Owner, scale);
    m_SkillList[SKILL_E] = new TeleportSkill(m_Owner);
}


Magician::~Magician()
{
    GGameManager->GetWolrd()->DestroyBody(m_Body);
    for (auto& skill : m_SkillList)
    {
        delete skill.second;
    }
}