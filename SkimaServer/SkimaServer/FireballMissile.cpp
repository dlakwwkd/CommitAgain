#include "stdafx.h"
#include "FireballMissile.h"
#include "GameManager.h"


FireballMissile::FireballMissile()
{
}

FireballMissile::FireballMissile(int playerId, b2Vec2 initPos, b2Vec2 targetPos)
{
	m_PlayerID = playerId;
	m_unitType = UNIT_MISSILE;
	m_TargetPos = targetPos;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(initPos.x, initPos.y);
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
}


FireballMissile::~FireballMissile()
{
	//GGameManager->GetWolrd()->DestroyBody(m_Body);

}
