#include "stdafx.h"
#include "SparkSkill.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Missile.h"
#include "Player.h"
#include "Hero.h"


SparkSkill::SparkSkill(int playerid, float heroBodySize)
{
	m_PlayerId = playerid;
	m_Damage = 500;
	m_MissileSpeed = REDUCE(1200);
	m_MissileLiveTime = 500.0f;
	m_HeroBodySize = heroBodySize;

	m_Range = REDUCE(800);
	m_Hp = 100;
}


SparkSkill::~SparkSkill()
{
}

void SparkSkill::SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos)
{
	b2Vec2 initPos = GenerateInitPos(heroPos, targetPos);

    auto hero = GGameManager->SearchPlayer(m_PlayerId)->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto client = GClientManager->GetClient(m_PlayerId);
    client->SkillBroadCast(hero->GetUnitID(), skillType, SKILL_Q, heroPos, targetPos);

	auto missile = static_cast<Missile*>(GObjectManager->Assign(UNIT_MISSILE));
	auto player = GGameManager->SearchPlayer(m_PlayerId);
    player->UnitListPush(missile->GetUnitID(), missile);

	missile->SetMissileInit(m_PlayerId, MS_SPARK, initPos, DEF_SCALE);
	missile->SetMissileTargetPos(targetPos);
	missile->SetMissileSpeed(m_MissileSpeed);
	missile->SetMissileDamage(m_Damage);
	missile->SetMissileLivetime(m_MissileLiveTime);
	missile->SetMissileRange(m_Range);
	missile->SetMissileHp(m_Hp);
	missile->MissileShoot();
}