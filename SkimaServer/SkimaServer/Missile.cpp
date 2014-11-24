#include "stdafx.h"
#include "Missile.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"


Missile::Missile()
{
	m_UnitType = UNIT_MISSILE;
	m_Damage = 0;
	m_Range = 0.0f;
	m_Livetime = 0.0f;
}

Missile::~Missile()
{
}


void Missile::SetMissileInit(int playerId, b2Vec2 initPos)
{
	m_PlayerID = playerId;
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
	auto direction = m_TargetPos - currentPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	b2Vec2 rangePos;
	rangePos.x = direction.x*m_Range / distance;
	rangePos.y = direction.y*m_Range / distance;
	m_TargetPos = rangePos;

	direction = rangePos - currentPos;
	distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);

	GClientManager->GetClient(m_PlayerID)->MissileBroadCast(m_PlayerID, m_UnitID, currentPos, m_TargetPos);
	m_State->TryMove(this);
}

void Missile::ConsumeLiveTime(float costTime)
{

}