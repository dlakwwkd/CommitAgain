#include "stdafx.h"
#include "ShootingSkill.h"

ShootingSkill::ShootingSkill()
{

}

ShootingSkill::ShootingSkill(int playerId)
{
	m_PlayerId = playerId;
	m_MissileSpeed = 0;
}

ShootingSkill::~ShootingSkill()
{
}

void ShootingSkill::ShootSkill(int unitId, b2Vec2 initPos, b2Vec2 targetPos)
{

}

b2Vec2 ShootingSkill::GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
// todo : ������ �ִ°������ ���� �´� ��춧���� �ϴ� �ϵ��ڵ�

	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= 5 / distance; //��ġ �����ʿ�

	return direction;

}

int ShootingSkill::MakeMissileUnitId(int playerId)
{

}
