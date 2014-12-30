#include "stdafx.h"
#include "IceballSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Missile.h"

IceballSkill::IceballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 45;
    m_MissileType = MS_ICE_BALL;
    m_MissileSpeed = Reduce(800.0f);
    m_MissileScale = DEF_SCALE;
	m_HeroBodySize = Reduce(heroBodySize);
    m_Range = Reduce(800.0f);
    m_MissileHp = 1000;
}


IceballSkill::~IceballSkill()
{
}

void IceballSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}
