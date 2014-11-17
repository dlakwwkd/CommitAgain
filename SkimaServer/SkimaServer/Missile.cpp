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
	m_unitType = UNIT_MISSILE;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(initPos.x,initPos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 10.0f / PTM_RATIO;
}


Missile::~Missile()
{
}

void Missile::MissileShoot()
{
	auto currentPos = m_Body->GetPosition();
	auto direction = m_TargetPos - m_Body->GetPosition();
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);

	GClientManager->GetClient(m_PlayerID)->MissileBroadCast(m_UnitID, currentPos, m_TargetPos);
	//todo : 코드추가및 검증필요
}

void Missile::ConsumeLiveTime(float costTime)
{

}

void Missile::BeginCrashed()
{
	m_Body->SetLinearDamping(10.0f);
}

void Missile::Crashing(bool isCrashing)
{
	GClientManager->GetClient(m_PlayerID)->CrashedBroadCast(m_UnitID, m_unitType, m_Body->GetPosition(), m_Body->GetPosition(), isCrashing);
	delete this;
}
