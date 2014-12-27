#pragma once
#include "Unit.h"
#include "ObjectPool.h"
class Timer;
class Game;

class Mob : public Unit, public ObjectPool<Mob>
{
public:
	Mob();
	virtual ~Mob();

    void    ChaseEnemy();
    void    Chasing();
    void    DeadMob();

private:
    Timer*  m_Timer = nullptr;
    Game*   m_Game = nullptr;

};

