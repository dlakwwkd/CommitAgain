#include "stdafx.h"
#include "Magician.h"
#include "FireballSkill.h"
#include "TeleportSkill.h"
#include "GameManager.h"


Magician::Magician(int playerId, b2Vec2 pos, float scale)
{
	m_PlayerID = playerId;
	m_Hp = m_MaxHp = 300;
	m_Speed = 10.0f;
	m_HeroType = HERO_MAGICIAN;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);
	
	b2CircleShape circle;
	circle.m_radius = scale / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;

	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);
	
	m_SkillList[SKILL_Q] = new FireballSkill(m_PlayerID, circle.m_radius);
	m_SkillList[SKILL_E] = new TeleportSkill(m_PlayerID);
}


Magician::~Magician()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
	for (auto& skill : m_SkillList)
	{
		delete skill.second;
	}
}

void Magician::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
	m_SkillList[skillKey]->SkillCast(m_UnitID, heroPos, targetPos);
}
