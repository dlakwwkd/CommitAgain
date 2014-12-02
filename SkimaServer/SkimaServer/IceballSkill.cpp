#include "stdafx.h"
#include "IceballSkill.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Missile.h"
#include "Player.h"
#include "Hero.h"

IceballSkill::IceballSkill(int playerid, float heroBodySize)
{
    m_PlayerId = playerid;

	///# 이제 이런 콘텐츠에 종속적인 값들은 따로 빼야지? xml 또는 json으로 외부에서 빌드하지 않고 수정 가능하도록...
    m_Damage = 50; 
    m_MissileSpeed = REDUCE(800);
    m_MissileLiveTime = 500.0f;
    m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
    m_Hp = 100;
}


IceballSkill::~IceballSkill()
{
}

void IceballSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    b2Vec2 initPos = GenerateInitPos(heroPos, targetPos);

    auto missile = static_cast<Missile*>(GObjectManager->Assign(UNIT_MISSILE));
    auto player = GGameManager->SearchPlayer(m_PlayerId);
    player->UnitListPush(missile->GetUnitID(), missile);

    missile->SetMissileInit(m_PlayerId, MS_ICE_BALL, initPos, DEF_SCALE);
    missile->SetMissileTargetPos(targetPos);
    missile->SetMissileSpeed(m_MissileSpeed);
    missile->SetMissileDamage(m_Damage);
    missile->SetMissileLivetime(m_MissileLiveTime);
    missile->SetMissileRange(m_Range);
    missile->SetMissileHp(m_Hp);
    missile->MissileShoot();
}
