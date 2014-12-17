#pragma once
#include "..\..\PacketType.h"
#include "RefCountable.h"
class Unit;
class Missile;

#define INIT_POOL_SIZE 1000

class UnitPoolManager : public RefCountable
{
public:
    UnitPoolManager();
    virtual ~UnitPoolManager();

    Unit*   Assign(UnitType type);
    void    Release(Unit* unit);
    void    Except(Unit* unit);
private:
    Unit*   Expand(UnitType type);

private:
	std::vector<Missile*>   m_MissileList;
    int                     m_LastID_Missile;
};

extern UnitPoolManager* GUnitPoolManager;