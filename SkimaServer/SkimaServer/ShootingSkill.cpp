#include "stdafx.h"
#include "ShootingSkill.h"

ShootingSkill::ShootingSkill()
{

}

ShootingSkill::ShootingSkill(int playerId, float heroBodySize)
{
	m_PlayerId = playerId;
	m_MissileSpeed = 0;
	m_HeroBodySize = heroBodySize;
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