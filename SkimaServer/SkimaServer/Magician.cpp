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
	
	m_Qskill = new FireballSkill(m_PlayerID, m_Body->GetFixtureList()->GetShape()->m_radius);
	

}


Magician::~Magician()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}

void Magician::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
	printf("[DEBUG] Magician :: UseSkill\n");
	//broadcast skill id , unit pos...
	//skill id == missile unit id
	switch (skillKey)
	{
	case SKILL_NONE:
		break;

	case SKILL_Q:
		m_Qskill->ShootSkill(m_UnitID,heroPos,targetPos);
		break;

	case SKILL_W:
		break;

	case SKILL_E:
		break;

	case SKILL_R:
		break;

	}
}
		
