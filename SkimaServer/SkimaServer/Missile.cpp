#include "stdafx.h"
#include "Missile.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"



Missile::Missile()
{

}


Missile::Missile(int unitId, int missileId, b2Vec2 initPos, b2Vec2 targetPos)
{

}


Missile::~Missile()
{
}

void Missile::SetMissileInit(int playerId, b2Vec2 initPos)
{
	m_PlayerID = playerId;
	m_UnitType = UNIT_MISSILE;

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

void Missile::MissileShoot()
{
	auto currentPos = m_Body->GetPosition();
	GClientManager->GetClient(m_PlayerID)->MissileBroadCast(m_PlayerID, m_UnitID, currentPos, m_TargetPos);
	m_State->TryMove(this);
}

void Missile::ConsumeLiveTime(float costTime)
{

}
// 
// void Missile::BeginCrashed()
// {
// 	m_Body->SetLinearDamping(10.0f);
// }
// 
// void Missile::Crashing(bool isCrashing)
// {
// 	GClientManager->GetClient(m_PlayerID)->CrashedBroadCast(m_UnitID, m_unitType, m_Body->GetPosition(), m_Body->GetPosition(), isCrashing);
// }
