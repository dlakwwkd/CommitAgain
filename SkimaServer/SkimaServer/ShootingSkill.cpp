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

void ShootingSkill::ShootSkill(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{

}

b2Vec2 ShootingSkill::GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
	// todo : 가까이 있는곳에쏘면 내가 맞는 경우고려

	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= (2.5f*2*m_HeroBodySize) / distance; //수치 수정필요 ==> hero의 size를 받을것

	return direction;

}