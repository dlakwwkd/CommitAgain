#include "stdafx.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "FlashSkill.h"

Jupiter::Jupiter(Player* owner, b2Vec2 pos, float scale)
{
	m_Owner = owner;
	m_UnitID = SET_SIDE_TYPE(m_UnitID, HERO_JUPITER);
	m_Hp = m_MaxHp = 1000;
	m_Speed = REDUCE(500);

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

    m_SkillList[SKILL_Q] = new SparkSkill(m_Owner, circle.m_radius);
    m_SkillList[SKILL_W] = new LightningSkill(m_Owner);
    m_SkillList[SKILL_E] = new FlashSkill(m_Owner);
}


Jupiter::~Jupiter()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
	for (auto& skill : m_SkillList)
	{
		delete skill.second;
	}
}