#include "stdafx.h"
#include "ShootingSkill.h"
#include "GameManager.h"

ShootingSkill::ShootingSkill()
{
	m_MissileSpeed = 0.0f;
	m_MissileLiveTime = 0.0f;
	m_Range = 0.0f;
	m_Hp = 0;
}


ShootingSkill::~ShootingSkill()
{
}


void ShootingSkill::SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{

}

b2Vec2 ShootingSkill::GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
	auto displacement = targetPos - heroPos;
    displacement.Normalize();
    displacement *= m_HeroBodySize + REDUCE(64);
    displacement += heroPos;
    return displacement;
}