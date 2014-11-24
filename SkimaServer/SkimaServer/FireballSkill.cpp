#include "stdafx.h"
#include "FireballSkill.h"
#include "FireballMissile.h"
#include "MissileManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Hero.h"

FireballSkill::FireballSkill(int playerid, float heroBodySize)
{
	m_PlayerId = playerid;
	m_Damage = 50;
	m_MissileSpeed = 10.0f;
	m_MissileLiveTime = 500.0f;
	m_HeroBodySize = heroBodySize;

	m_Missile = GMissileManager->Assign(MS_FIRE_BALL);
	auto player = GGameManager->SearchPlayer(playerid);
	player->UnitListPush(m_Missile->GetUnitID(), m_Missile);
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{
	b2Vec2 initPos = GenerateInitPos(heroPos, targetPos);

	m_Missile->SetMissileInit(m_PlayerId, initPos, DEF_SCALE);
	m_Missile->SetMissileTargetPos(targetPos);
	m_Missile->SetMissileSpeed(m_MissileSpeed);
	m_Missile->SetMissileDamage(m_Damage);
	m_Missile->SetMissileLivetime(m_MissileLiveTime);
	m_Missile->MissileShoot();
}
