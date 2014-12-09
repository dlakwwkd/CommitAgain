#include "stdafx.h"
#include "Player.h"
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
    case HERO_MAGICIAN:
        m_Hero = new Magician(this, pos, DEF_SCALE);
        break;
    case HERO_JUPITER:
        m_Hero = new Jupiter(this, pos, DEF_SCALE);
        break;
    default:
        return;
    };
    m_UnitList[m_Hero->GetUnitID()] = m_Hero;

    m_Client->SendCreateHeroResult(m_Hero->GetUnitID(), pos);
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

