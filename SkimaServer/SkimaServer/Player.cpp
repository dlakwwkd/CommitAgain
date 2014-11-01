#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Unit(pos);
	auto client = GClientManager->GetClient(m_PlayerID);
	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetUnitType(), m_Hero->GetCurrentPos());
}

void Player::UnitMove(b2Vec2 currentPos, b2Vec2 targetPos, int speed)
{

}

