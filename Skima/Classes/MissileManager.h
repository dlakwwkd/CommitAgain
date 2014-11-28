#pragma once
#include "..\..\PacketType.h"
class Missile;

enum InitPoolSize
{
	TOTAL		= 100,
	FIRE_BALL	= 50,
	ICE_BALL	= 50,
};

enum IDBoundary
{
	ID_INTERVAL			= 200,
	MISSILE_ID_START	= 1001,
	FIRE_BALL_ID_START	= MISSILE_ID_START + ID_INTERVAL,
	ICE_BALL_ID_START	= FIRE_BALL_ID_START + ID_INTERVAL,
};

class MissileManager
{
public:
	MissileManager();
	~MissileManager();

	Missile*	Assign(int unitId, MissileType type);
	void		Release(Missile* missile);
private:
	bool		Expand(MissileType type);

private:
	std::vector<Missile*>	m_MissileList;

	int						m_LastID_FireBall;
	int						m_LastID_IceBall;
};

