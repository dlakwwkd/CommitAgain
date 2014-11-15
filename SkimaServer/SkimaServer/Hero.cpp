#include "stdafx.h"
#include "Hero.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"



Hero::Hero()
{

}

Hero::Hero(int playerId, HeroType heroType, b2Vec2 pos)
{
	m_UnitID = -1;
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



void Hero::UseSkill(SkillKey skillKey, b2Vec2 targetPos)
{

}
