#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, b2Vec2 pos)
: m_ID(-1), m_Type(TYPE_NONE), m_Speed(5), m_TargetPos({ 0, 0 }),
m_AverageMove({ 0, 0 }), m_PlayerId(playerId)
{
	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;

	m_BodyDef.type = b2_dynamicBody;
	m_BodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&m_BodyDef);

	b2CircleShape circle;
	circle.m_radius = 10.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;
	
	m_Body->CreateFixture(&fixtureDef);
	//m_Body->SetLinearDamping(0.1f);

	static int makeId = 0;
	m_ID = ++makeId;
}


Unit::~Unit()
{
}

void Unit::UnitMove()
{
	if (!(m_Body->GetPosition().x < m_TargetPos.x - 5 ||
		m_Body->GetPosition().y < m_TargetPos.y - 5 ||
		m_Body->GetPosition().x > m_TargetPos.x + 5 ||
		m_Body->GetPosition().y > m_TargetPos.y + 5))
	{
		EndMove();
		return;
	}
	auto currentPos = (m_Body->GetPosition() + m_AverageMove);
	m_Body->SetTransform(currentPos, 0);

	printf("id: %d, x: %f, y: %f \n", m_ID, m_Body->GetPosition().x, m_Body->GetPosition().y);

	if (0)
	{
		Crashed();
	}
}

void Unit::SetAverageMove(b2Vec2 targetPos)
{
	auto direction = targetPos - m_Body->GetPosition();
	auto temp = abs(direction.x) + abs(direction.y);

	direction *= m_Speed / temp;

	m_AverageMove = direction;
}

void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_BodyDef.position.Set(currentPos.x, currentPos.y);
	m_TargetPos = targetPos;
	SetAverageMove(targetPos);
	m_State->TryMove(this);
}

void Unit::UnitCrashed(bool isCrashed)
{
	GClientManager->GetClient(m_PlayerId)->CrashedBoradCast(m_ID, m_Body->GetPosition(), isCrashed);
}
