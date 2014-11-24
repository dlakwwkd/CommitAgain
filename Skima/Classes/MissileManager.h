#pragma once
#include "..\..\PacketType.h"
class Missile;

enum InitPoolSize
{
	TOTAL		= 1000,
	FIRE_BALL	= 200,
	ICE_BALL	= 200,
};

enum IDBoundary
{
	ID_INTERVAL			= 1000,
	MISSILE_ID_START	= 10001,
	FIRE_BALL_ID_START	= MISSILE_ID_START + ID_INTERVAL,
	ICE_BALL_ID_START	= FIRE_BALL_ID_START + ID_INTERVAL,
};

class MissileManager
{
public:
	MissileManager();
	virtual ~MissileManager();

	Missile*	Assign(int unitId, MissileType type);
	void		Release(Missile* missile);
private:
	bool		Expand(MissileType type);

private:
	std::vector<Missile*>	m_MissileList;

	int						m_LastID_FireBall;
	int						m_LastID_IceBall;
};

