#include "stdafx.h"
#include "ShootingSkill.h"

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
	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	
	direction.x = (direction.x*m_HeroBodySize * 2.5f) / distance;
	direction.y = (direction.y*m_HeroBodySize * 2.5f) / distance;

	heroPos += direction;
	return heroPos;
}