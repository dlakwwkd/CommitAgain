#pragma once
#include "Unit.h"

class Player
{
public:
	Player(int playerId) : m_PlayerID(playerId){}
	~Player(){ delete m_Hero; }

	Unit*	GetMyHero(){ return m_Hero; }
	void	CreateHero(b2Vec2 pos);
	void	UnitMove(b2Vec2 currentPos, b2Vec2 targetPos, int speed);

private:
	int		m_PlayerID;
	Unit*	m_Hero;
};

