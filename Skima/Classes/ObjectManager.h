#pragma once
#include "..\..\PacketType.h"
class Unit;
class Missile;

#define INIT_POOL_SIZE 1000

class ObjectManager
{
public:
	ObjectManager();
	virtual ~ObjectManager();

	Unit* Assign(int unitId);
	void	Release(Unit* unit);
private:
	Unit* Expand(int unitId);

private:
	std::vector<Missile*>	m_MissileList;
	int					    m_LastID_Missile;
};
