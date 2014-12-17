#pragma once
#include "..\..\PacketType.h"
#include "RefCountable.h"
#include <unordered_map>
class Unit;

typedef std::unordered_multimap<UnitType, Unit*> UnitPoolList;

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
	UnitPoolList	m_UnitPoolList;
	int				m_LastID_Missile;
	int				m_LastID_Mob;
};

extern UnitPoolManager* GUnitPoolManager;