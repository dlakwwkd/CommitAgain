#include "stdafx.h"
#include "Rock.h"
#include "GameManager.h"


Rock::Rock(Player* owner, b2Vec2 pos)
{
    m_Owner = owner;
    m_Hp = 1000;
    m_Pos = pos;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(m_Pos.x, m_Pos.y);
    
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2PolygonShape square;
    square.SetAsBox(REDUCE(30.0f), REDUCE(60.0f));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &square;
    fixtureDef.density = 2.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 3.0f;
    
    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}


Rock::~Rock()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}
