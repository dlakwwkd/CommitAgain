#include "stdafx.h"
#include "MapObject.h"
#include "GameManager.h"


MapObject::MapObject()
{
//     m_Owner = nullptr;
//     m_Hp = 10000;
//     m_Damage = 100;
//     m_Pos.x = 100;
//     m_Pos.y = 100;
// 
//     b2BodyDef bodyDef;
//     bodyDef.type = b2_staticBody;
//     bodyDef.position.Set(m_Pos.x, m_Pos.y);
//     m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);
// 
//     b2PolygonShape square;
//     square.SetAsBox(10, 5);
// 
//     b2FixtureDef fixtureDef;
//     fixtureDef.shape = &square;
//     fixtureDef.density = 1.0f;
//     fixtureDef.friction = 0.3f;
//     fixtureDef.restitution = 0.7f;
// 
//     m_Body->CreateFixture(&fixtureDef);
//     m_Body->SetUserData(this);
}


MapObject::~MapObject()
{
}
