#include "stdafx.h"
#include "Missile.h"
#include "Scheduler.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "MissileManager.h"
#include "Player.h"


Missile::Missile()
{
	m_UnitType = UNIT_MISSILE;
	m_MissileType = MS_NONE;
	m_InUse = false;
	m_Range = 0.0f;
	m_Livetime = 0.0f;
}

Missile::~Missile()
{
	GMissileManager->Release(this);
}


void Missile::SetMissileInit(int playerId, b2Vec2 initPos, float scale)
{
	m_PlayerID = playerId;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(initPos.x, initPos.y);
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
}

void Missile::MissileShoot()
{
	auto currentPos = m_Body->GetPosition();
	auto direction = m_TargetPos - currentPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	b2Vec2 rangePos;
	rangePos.x = direction.x*m_Range / distance + currentPos.x;
	rangePos.y = direction.y*m_Range / distance + currentPos.y;
	m_TargetPos = rangePos;

	auto newDirection = rangePos - currentPos;
	newDirection *= m_Speed / m_Range;

	m_Body->SetLinearVelocity(newDirection);

	GClientManager->GetClient(m_PlayerID)->MissileBroadCast(m_PlayerID, m_UnitID, currentPos, m_TargetPos);
	m_State->TryMove(this);
}

void Missile::ConsumeLiveTime(float costTime)
{

}

void Missile::Extinction()
{
	Crashing(false);

	auto player = GGameManager->SearchPlayer(m_PlayerID);
	player->UnitListPop(m_UnitID);

	if (m_InUse)
	{
		CallFuncAfter(1, GMissileManager, &MissileManager::Release, this);
	}
}
