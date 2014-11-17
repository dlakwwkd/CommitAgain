#pragma once
#include "Hero.h"

class Player
{
public:
	Player(int playerId) : m_PlayerID(playerId){}
	~Player(){ delete m_Hero; }

	Hero*	GetMyHero(){ return m_Hero; }
	void	SetHeroType(HeroType herotype) { m_HeroType = herotype; }
	void	CreateHero(int unitId, b2Vec2 pos);

private:
	int			m_PlayerID;
	Hero*		m_Hero;
	HeroType	m_HeroType;
};

