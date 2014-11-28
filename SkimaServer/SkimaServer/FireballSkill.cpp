﻿#include "stdafx.h"
#include "FireballSkill.h"
#include "FireballMissile.h"
#include "MissileManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Hero.h"

FireballSkill::FireballSkill(int playerid, float heroBodySize)
{
	m_PlayerId = playerid;
	m_Damage = 100;
    m_MissileSpeed = REDUCE(600);
	m_MissileLiveTime = 500.0f;
	m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
	m_Hp = 100;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{
	b2Vec2 initPos = GenerateInitPos(heroPos, targetPos);

	auto missile = GMissileManager->Assign(MS_FIRE_BALL);
	auto player = GGameManager->SearchPlayer(m_PlayerId);
	player->UnitListPush(missile->GetUnitID(), missile);

	missile->SetMissileInit(m_PlayerId, initPos, DEF_SCALE);
	missile->SetMissileTargetPos(targetPos);
	missile->SetMissileSpeed(m_MissileSpeed);
	missile->SetMissileDamage(m_Damage);
	missile->SetMissileLivetime(m_MissileLiveTime);
	missile->SetMissileRange(m_Range);
	missile->SetMissileHp(m_Hp);
	missile->MissileShoot();
}
