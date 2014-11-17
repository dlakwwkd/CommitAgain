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
	// todo : ������ �ִ°������ ���� �´� �����

	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= (2.5f*2*m_HeroBodySize) / distance; //��ġ �����ʿ� ==> hero�� size�� ������

	return direction;

}