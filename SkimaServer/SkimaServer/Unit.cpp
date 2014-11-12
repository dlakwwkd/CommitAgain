#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, b2Vec2 pos)
: m_UnitID(-1), m_Type(TYPE_NONE), m_Speed(10.0f), m_TargetPos({ 0, 0 }), m_PlayerID(playerId)
{
	static int makeId = 0;
	m_UnitID = ++makeId;

	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 15.0f/PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;
	
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);
}

Unit::~Unit()
{
	delete m_StandbyState;
	delete m_MovingState;
	delete m_CrashedState;
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}


void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_TargetPos = targetPos;

	auto direction = targetPos - m_Body->GetPosition();
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	if (distance < 0.4f)
	{
		m_Body->SetLinearVelocity(b2Vec2(0, 0));
		return;
	}

	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);

	GClientManager->GetClient(m_PlayerID)->SendUnitInfo(m_UnitID, m_Type, currentPos, targetPos);

	m_State->TryMove(this);
}


void Unit::UnitMove()
{
	if (!(m_Body->GetPosition().x < m_TargetPos.x - 0.1f ||
		m_Body->GetPosition().y < m_TargetPos.y - 0.1f ||
		m_Body->GetPosition().x > m_TargetPos.x + 0.1f ||
		m_Body->GetPosition().y > m_TargetPos.y + 0.1f))
	{
		printf(" - Reach: UnitID:  %d, \t\t\t\t\t X : %.f\tY : %.f\n", m_UnitID,
			m_Body->GetPosition().x*PTM_RATIO, m_Body->GetPosition().y*PTM_RATIO);
		EndMove();
	}
}

void Unit::UnitCrashed()
{
	auto client = GClientManager->GetClient(m_PlayerID);		_ASSERT(client != nullptr);

	auto velo = m_Body->GetLinearVelocity();
	auto pos = m_Body->GetPosition();

	printf("Velocity unitId: %d, x: %f, y: %f\n", m_UnitID, velo.x, velo.y);

	b2Vec2 expectpos;

	expectpos.x = pos.x + velo.x; //¿¹»ó °ª
	expectpos.y = pos.y + velo.y;

	client->CrashedBoradCast(m_UnitID, expectpos);
}
