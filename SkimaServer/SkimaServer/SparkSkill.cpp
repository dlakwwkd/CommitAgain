#include "stdafx.h"
#include "SparkSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Hero.h"
#include "Missile.h"


SparkSkill::SparkSkill(Player* owner, float heroBodySize)
{
	m_Owner = owner;
	m_Damage = 350;
    m_MissileType = MS_SPARK;
	m_MissileSpeed = Reduce(1300.0f);
    m_MissileScale = DEF_SCALE;
	m_HeroBodySize = Reduce(heroBodySize);
	m_Range = Reduce(800.0f);
	m_MissileHp = 100;
}


SparkSkill::~SparkSkill()
{
}

void SparkSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}