﻿#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Magician.h"
#include "Jupiter.h"


Player::~Player()
{
    UnitListClear();
}

void Player::CreateHero(b2Vec2 pos)
{
    switch (m_HeroType)
    {
    default: ///# 디폴트는 맨 아래로 보내는 습관을 들일 것... 
    case HERO_NONE: return;
    case HERO_MAGICIAN:
        m_Hero = new Magician(m_PlayerID, pos, DEF_SCALE);
        break;
    case HERO_JUPITER:
		m_Hero = new Jupiter(m_PlayerID, pos, DEF_SCALE);
        break;
    }
    m_UnitList[m_Hero->GetUnitID()] = m_Hero; ///# 맵을 이런식으로 쓰는 것은 지양.. key가 있는지에 대한 평가하는 방식으로 써야 안전하다.

    auto client = GClientManager->GetClient(m_PlayerID);
    client->SendCreateHeroResult(m_Hero->GetUnitID(), pos);
}

void Player::UnitListPop(int unitID)
{
    auto unit = m_UnitList.find(unitID);
    if (unit != m_UnitList.end())
    {
        m_UnitList.erase(unit);
        printf(" - UnitListPop() : player %d : unitList.size : %d \n", m_PlayerID, m_UnitList.size());
    }
}

void Player::UnitListClear()
{
    if (m_Hero != nullptr)
    {
        m_UnitList.erase(m_Hero->GetUnitID());
        delete m_Hero;
        m_Hero = nullptr;
    }
    for (auto& unit : m_UnitList)
    {
        unit.second->Extinction();
    }
    m_UnitList.clear();
    printf(" - UnitListClear() : player %d \n", m_PlayerID);
}

