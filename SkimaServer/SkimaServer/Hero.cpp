#include "stdafx.h"
#include "Hero.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"



Hero::Hero()
{

}

Hero::Hero(int playerId, int unitId, HeroType heroType, b2Vec2 pos)
{
	m_UnitID = unitId;
	m_unitType = UNIT_HERO;
	m_HeroType = heroType;
	m_Speed = 10.0f;
	m_TargetPos = { 0, 0 };
	m_PlayerID = playerId;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
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

	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;
}


Hero::~Hero()
{
	
}



void Hero::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
	//각각의 캐릭터의 useskill만 호출 (검증필요..)
}

void Hero::UnitMove()
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
void Hero::Crashing(bool isCrashing)
{
	auto client = GClientManager->GetClient(m_PlayerID);		_ASSERT(client != nullptr);

	auto velo = m_Body->GetLinearVelocity();
	velo.x *= 5;
	velo.y *= 5;
	m_Body->SetLinearVelocity(velo);
	auto pos = m_Body->GetPosition();

	printf("Velocity unitId: %d, x: %f, y: %f\n", m_UnitID, velo.x*PTM_RATIO, velo.y*PTM_RATIO);

	b2Vec2 expectpos;

	expectpos.x = pos.x + velo.x * CRASHTIME; //예상 값
	expectpos.y = pos.y + velo.y * CRASHTIME;

	client->CrashedBroadCast(m_UnitID, m_unitType, m_Body->GetPosition(), expectpos, isCrashing);
}