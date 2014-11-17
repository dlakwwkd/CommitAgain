#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Magician.h"


void Player::CreateHero(b2Vec2 pos)
{
	//switch로 거르기
	m_Hero = new Magician(m_PlayerID, m_HeroType, pos);
	auto client = GClientManager->GetClient(m_PlayerID);

	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetHeroType(), pos);
}

