#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, b2Vec2 pos)
{
	static int makeId = 0;
	m_UnitID = ++makeId;
	
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
	fixtureDef.restitution = 0.7f;
	
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);
}

Unit::Unit()
{

}

Unit::~Unit()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}

