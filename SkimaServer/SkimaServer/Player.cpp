#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Unit(pos);
	auto client = GClientManager->GetClient(m_PlayerID);

	Sleep(500);

	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetUnitType(), m_Hero->GetCurrentPos());
}

