#include "stdafx.h"
#include "TeleportSkill.h"


TeleportSkill::TeleportSkill()
{
	m_Range = 20.0f;
}

TeleportSkill::TeleportSkill(int playerId)
{
	m_Range = 20.0f;
	m_PlayerId = playerId;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{
	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		
	if (distance <= m_Range)
	{
		//todo : ���־��̵�� hero�޾Ƽ� m_body�� direction���� �̵�
	}

	else
	{
		direction.x = direction.x / distance;
		direction.y = direction.y / distance;

		b2Vec2 rangePos; 
		rangePos.x = direction.x*m_Range;
		rangePos.y = direction.y*m_Range;

		//todo : ���־��̵�� hero�޾Ƽ� m_body�� rangePos�� �̵� 
	}
}
