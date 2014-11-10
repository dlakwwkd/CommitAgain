#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, b2Vec2 pos)
: m_UnitID(-1), m_Type(TYPE_NONE), m_Speed(10.0f), m_TargetPos({ 0, 0 }), m_PlayerId(playerId)
{
	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 10.0f/PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;
	
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);

	static int makeId = 0;
	m_UnitID = ++makeId;
}


Unit::~Unit()
{
}

void Unit::UnitMove()
{
	if (!(m_Body->GetPosition().x < m_TargetPos.x - 0.05f ||
		m_Body->GetPosition().y < m_TargetPos.y - 0.05f ||
		m_Body->GetPosition().x > m_TargetPos.x + 0.05f ||
		m_Body->GetPosition().y > m_TargetPos.y + 0.05f))
	{
		printf("id: %d, x: %f, y: %f \n", m_UnitID, m_Body->GetPosition().x*PTM_RATIO, m_Body->GetPosition().y*PTM_RATIO);
		m_Body->SetLinearVelocity(b2Vec2(0, 0));
		EndMove();
		return;
	}

// 	auto currentPos = (m_Body->GetPosition() + m_AverageMove);
// 	m_Body->SetTransform(currentPos, 0);

// 	if (1)
// 	{
// 		Crashed();
// 	}
}

void Unit::SetAverageMove(b2Vec2 targetPos)
{
	auto direction = targetPos - m_Body->GetPosition();
	auto temp = abs(direction.x) + abs(direction.y);

	direction *= m_Speed / temp;

	m_Body->SetLinearVelocity(direction);
}

void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_TargetPos = targetPos;
	SetAverageMove(targetPos);

	m_State->TryMove(this);
}

void Unit::UnitCrashed(bool isCrashed)
{
	GClientManager->GetClient(m_PlayerId)->CrashedBoradCast(m_UnitID, m_Body->GetPosition(), isCrashed);
}
