#pragma once
#include "Unit.h"
class Mob;
class Timer;

class Item : public Unit
{
public:
    Item(Mob* mob, BuffTarget type);
    virtual ~Item();

    BuffTarget      GetBuffTarget() { return m_BuffType; }

    virtual void    Dead();

private:
    BuffTarget  m_BuffType;
    Timer*      m_Timer = nullptr;
};

