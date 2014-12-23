#include "stdafx.h"
#include "Player.h"
#include "ClientSession.h"
#include "Magician.h"
#include "Jupiter.h"
#include "Laphinx.h"

Player::~Player()
{
    UnitListClear();
}

void Player::CreateHero(const b2Vec2& pos)
{
    switch (m_HeroType)
    {
    case HERO_MAGICIAN: m_Hero = new Magician(this, pos, DEF_SCALE);break;
    case HERO_JUPITER:  m_Hero = new Jupiter(this, pos, DEF_SCALE);	break;
    case HERO_LAPHINX:  m_Hero = new Laphinx(this, pos, DEF_SCALE);	break;
    default:
		return;
    };
    m_Client->SendCreateHeroResult(m_Hero->GetUnitID(), pos);
}

void Player::UnitListPop(int unitID)
{
    auto unit = m_UnitList.find(unitID);
    if (unit != m_UnitList.end())
    {
		delete unit->second;
		m_UnitList.erase(unit);
        printf(" - UnitListPop : player %d, size : %d \n", m_PlayerID, m_UnitList.size());
    }
}

void Player::UnitListClear()
{
    for (auto& unit : m_UnitList)
    {
        delete unit.second;
    }
    m_UnitList.clear();
	printf(" - UnitListClear : player %d, size : %d \n", m_PlayerID, m_UnitList.size());
}

