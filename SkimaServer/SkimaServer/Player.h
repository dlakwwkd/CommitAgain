#pragma once
#include "Unit.h"

class Player
{
public:
	Player(int playerId) : m_PlayerID(playerId){}
	~Player(){ delete m_Hero; }

	Unit*	GetMyHero(){ return m_Hero; }
	void	CreateHero(b2Vec2 pos);
	void	UnitMove();
	void	SetAverageMove(b2Vec2 targetPos);

private:
	int		m_PlayerID;
	Unit*	m_Hero;
};

