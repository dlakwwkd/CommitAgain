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

void TeleportSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
	auto direction = targetPos - heroPos;
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		
	if (distance <= m_Range)
	{
		auto hero = GGameManager->SearchPlayer(m_PlayerId)->GetMyHero();
		hero->GetBody()->SetTransform(targetPos, 0);

		auto client = GClientManager->GetClient(m_PlayerId);
		client->TeleportBroadCast(m_PlayerId,hero->GetUnitID(),heroPos,targetPos);
	}

	else
	{
		direction.x = direction.x / distance;
		direction.y = direction.y / distance;

		b2Vec2 rangePos; 
		rangePos.x = direction.x*m_Range;
		rangePos.y = direction.y*m_Range;

		auto hero = GGameManager->SearchPlayer(m_PlayerId)->GetMyHero();
		hero->GetBody()->SetTransform(rangePos, 0);

		auto client = GClientManager->GetClient(m_PlayerId);
		client->TeleportBroadCast(m_PlayerId,hero->GetUnitID(), heroPos, rangePos);
	}
}
