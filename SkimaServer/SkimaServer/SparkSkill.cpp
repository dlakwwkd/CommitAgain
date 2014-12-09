#include "stdafx.h"
#include "SparkSkill.h"
#include "ObjectManager.h"
#include "ClientSession.h"
#include "Player.h"
#include "Hero.h"
#include "Missile.h"


SparkSkill::SparkSkill(Player* owner, float heroBodySize)
{
	m_Owner = owner;
	m_Damage = 500;
    m_MissileType = MS_SPARK;
	m_MissileSpeed = REDUCE(1200);
    m_MissileScale = DEF_SCALE;
	m_HeroBodySize = heroBodySize;
	m_Range = REDUCE(800);
	m_MissileHp = 100;
}


SparkSkill::~SparkSkill()
{
}

void SparkSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));
}