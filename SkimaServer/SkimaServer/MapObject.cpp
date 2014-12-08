#include "stdafx.h"
#include "MapObject.h"
#include "GameManager.h"


MapObject::MapObject()
{
    m_PlayerID = 0;
    m_Hp = 10000;
    m_Damage = 100;
    m_Pos.x = 100;
    m_Pos.y = 100;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_Pos.x, m_Pos.y);
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2CircleShape circle; //여기서부터 수정 해야 한다
    circle.m_radius = REDUCE(DEF_SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}


MapObject::~MapObject()
{
}
