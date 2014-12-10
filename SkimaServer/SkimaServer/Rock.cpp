#include "stdafx.h"
#include "Rock.h"
#include "GameManager.h"


Rock::Rock(b2Vec2 pos)
{
    m_Owner = nullptr;
    m_UnitID; // 이거 처리 해야 됨...

    m_Hp = 10000;
    m_Pos.x = pos.x;
    m_Pos.y = pos.y;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(m_Pos.x, m_Pos.y);
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2PolygonShape square;
    square.SetAsBox(10, 5);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &square;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}


Rock::~Rock()
{
}
