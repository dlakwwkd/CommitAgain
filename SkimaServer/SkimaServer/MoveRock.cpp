#include "stdafx.h"
#include "MoveRock.h"
#include "GameManager.h"


MoveRock::MoveRock(Player* owner, b2Vec2 pos)
{
    m_Owner = owner;
    m_Hp = 1000;
    m_Pos = pos;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_Pos.x, m_Pos.y);

    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2CircleShape circle;
	circle.m_radius = REDUCE(5.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 2.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 3.0f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}


MoveRock::~MoveRock()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}
