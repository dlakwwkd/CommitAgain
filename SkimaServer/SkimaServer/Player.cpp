﻿#include "stdafx.h"
#include "Player.h"
#include "ClientSession.h"
#include "Magician.h"
#include "Jupiter.h"
#include "Laphinx.h"

Player::Player(ClientSession* client, const std::string& playerName, PlayerType type)
{
    m_PlayerID = MakeID(this);
    m_Client = client;
    m_PlayerName = playerName;
    m_PlayerType = type;
}

Player::~Player()
{
    UnitListClear();
}

void Player::CreateHero(const b2Vec2& pos, RoomType roomType)
{
    switch (m_HeroType)
    {
    case HERO_MAGICIAN: m_Hero = new Magician(this, pos, DEF_SCALE);break;
    case HERO_JUPITER:  m_Hero = new Jupiter(this, pos, DEF_SCALE);	break;
    case HERO_LAPHINX:  m_Hero = new Laphinx(this, pos, DEF_SCALE);	break;
    default:
		return;
    };
    m_Client->SendCreateHeroResult(m_Hero->GetUnitID(), pos, roomType);
}

void Player::DeadHero()
{
    m_Hero = nullptr;
}

void Player::UnitListPop(int unitID)
{
    auto unit = m_UnitList.find(unitID);
    if (unit != m_UnitList.end())
    {
		delete unit->second;
		m_UnitList.erase(unit);
        //printf(" - UnitListPop : player %d, size : %d \n", m_PlayerID, m_UnitList.size());
    }
}

void Player::UnitListClear()
{
    for (auto& unit : m_UnitList)
    {
        delete unit.second;
    }
    m_UnitList.clear();
	//printf(" - UnitListClear : player %d, size : %d \n", m_PlayerID, m_UnitList.size());
}

