#include "stdafx.h"
#include "IceballSkill.h"
#include "ObjectManager.h"
#include "ClientSession.h"
#include "Player.h"
#include "Missile.h"

IceballSkill::IceballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 300;
    m_MissileType = MS_ICE_BALL;
    m_MissileSpeed = REDUCE(800);
    m_MissileScale = DEF_SCALE;
    m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
    m_MissileHp = 100;
}


IceballSkill::~IceballSkill()
{
}

void IceballSkill::SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), key, heroPos, targetPos);
}
