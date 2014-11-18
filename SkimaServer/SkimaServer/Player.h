#pragma once
#include "Hero.h"

typedef std::map<int, Unit*> UnitList;

class Player
{
public:
	Player(int playerId) : m_PlayerID(playerId){}
	~Player(){ delete m_Hero; }

	Hero*			GetMyHero(){ return m_Hero; }
	UnitList&		GetUnitList(){ return m_UnitList; }
	void			SetHeroType(HeroType herotype) { m_HeroType = herotype; }
	void			SetUnitPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
	void			CreateHero(b2Vec2 pos);

private:
	int			m_PlayerID;
	Hero*		m_Hero;
	HeroType	m_HeroType;
	UnitList	m_UnitList;
	
};

