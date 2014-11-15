#include "stdafx.h"
#include "Missile.h"
#include "ClientManager.h"



Missile::Missile()
{

}

Missile::Missile(int playerId, b2Vec2 pos)
{

}


Missile::~Missile()
{
}

void Missile::MissileShoot(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_TargetPos = targetPos;

	auto direction = targetPos - m_Body->GetPosition();
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);

	GClientManager->GetClient(m_UnitID)->SendUnitInfo(m_UnitID, m_Type, currentPos, targetPos);
}
