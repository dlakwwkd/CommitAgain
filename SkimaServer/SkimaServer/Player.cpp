#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Hero(m_PlayerID, m_HeroType,pos);
	auto client = GClientManager->GetClient(m_PlayerID);

	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetHeroType(), pos);
}

