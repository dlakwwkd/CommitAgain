#include "stdafx.h"
#include "Missile.h"
#include "Scheduler.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Player.h"


Missile::Missile(int unitId)
{
    m_UnitID = unitId;
	m_Range = 0.0f;
	m_Livetime = 0.0f;
}

Missile::~Missile()
{
	GObjectManager->Release(this);
}

void Missile::SetMissileInit(int playerId, b2Vec2 initPos, float scale)
{
	m_PlayerID = playerId;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(initPos.x, initPos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = REDUCE(scale);

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
	auto displacement = m_TargetPos - currentPos;
	displacement.Normalize();
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    displacement *= m_Range / m_Speed;
    m_TargetPos = currentPos + displacement;

	GClientManager->GetClient(m_PlayerID)->MissileBroadCast(m_PlayerID, m_UnitID, currentPos, m_TargetPos);
	m_State->TryMove(this);
}

void Missile::ConsumeLiveTime(float costTime)
{

}

void Missile::Extinction()
{
	if (m_InUse)
	{
		CallFuncAfter(1, GObjectManager, &ObjectManager::Release, this);
	}
    printf("Extinction()!! : UnitID : %d \n", m_UnitID);
}
