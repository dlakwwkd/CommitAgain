#include "stdafx.h"
#include "TeleportSkill.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"

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
		auto player = GGameManager->SearchPlayer(m_PlayerId);
		player->GetMyHero()->GetBody()->SetTransform(targetPos, 0);

		auto client = GClientManager->GetClient(m_PlayerID);
		client->SendCreateHeroResult(m_Hero->GetUnitID(), m_Hero->GetHeroType(), pos);
	//보내주기
	}

	else
	{
		direction.x = direction.x / distance;
		direction.y = direction.y / distance;

		b2Vec2 rangePos; 
		rangePos.x = direction.x*m_Range;
		rangePos.y = direction.y*m_Range;

		auto player = GGameManager->SearchPlayer(m_PlayerId);
		player->GetMyHero()->GetBody()->SetTransform(rangePos, 0);

	}
}
