#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Unit(m_PlayerID, pos); ///# 이런거는 이렇게 수동으로 하면 자원 관리가 힘들다.. unique_ptr<> 사용을 고려해볼 것.
	auto client = GClientManager->GetClient(m_PlayerID);

	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetUnitType(), pos);
}

