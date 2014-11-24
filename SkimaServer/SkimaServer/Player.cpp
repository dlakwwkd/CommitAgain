#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Magician.h"


Player::~Player()
{
	for (auto& unit : m_UnitList)
	{
		delete unit.second;
	}
}

void Player::CreateHero(b2Vec2 pos)
{
	//switch로 거르기
	m_Hero = new Magician(m_PlayerID, pos, DEF_SCALE);
	m_UnitList[m_Hero->GetUnitID()] = m_Hero;

	auto client = GClientManager->GetClient(m_PlayerID);
	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetHeroType(), pos);
}

void Player::UnitListPop(int unitID)
{
	auto unit = m_UnitList.find(unitID);
	if (unit != m_UnitList.end())
	{
		m_UnitList.erase(unit);
	}
}

