#include "stdafx.h"
#include "Laphinx.h"
#include "GameManager.h"



Laphinx::Laphinx(Player* owner, b2Vec2 pos, float scale)
{
    m_Owner = owner;
    m_UnitID = SET_SIDE_TYPE(m_UnitID, HERO_MAGICIAN);
    m_Hp = m_MaxHp = 1000;
    m_Speed = REDUCE(360);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);
    
    b2CircleShape circle;
    circle.m_radius = REDUCE(scale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
    
//     m_SkillList[SKILL_Q] = new FireballSkill(m_Owner, circle.m_radius);
//     m_SkillList[SKILL_W] = new IceballSkill(m_Owner, circle.m_radius);
//     m_SkillList[SKILL_E] = new TeleportSkill(m_Owner);
}


Laphinx::~Laphinx()
{
    GGameManager->GetWolrd()->DestroyBody(m_Body);
    for (auto& skill : m_SkillList)
    {
        delete skill.second;
    }
}