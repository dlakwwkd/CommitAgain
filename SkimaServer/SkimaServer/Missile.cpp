#include "stdafx.h"
#include "Missile.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"



Missile::Missile()
{

}

Missile::Missile(int playerId, int unitId)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 10.0f / PTM_RATIO;
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
	//todo
}

void Missile::ConsumeLiveTime(int costTime)
{

}
