#include "stdafx.h"
#include "Magician.h"
#include "FireballSkill.h"
#include "GameManager.h"

Magician::Magician()
{
}

Magician::Magician(int playerId, HeroType heroType, b2Vec2 pos)
{
	m_PlayerID = playerId;
	m_HeroType = heroType;
	m_Hp = 300;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);
	
	b2CircleShape circle;
	circle.m_radius = 15.0f / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;

	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);
	
	m_HeroType = HERO_MAGICIAN;
	
	m_SkillList[SKILL_Q] = new FireballSkill(m_PlayerID,circle.m_radius);
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
