#pragma once
#include "Unit.h"
class Mob;
class Timer;

class Item : public Unit
{
public:
    Item(Mob* mob, BuffTarget buffType);
    virtual ~Item();

    BuffTarget      GetBuffTarget() { return m_BuffType; }

    virtual void    Dead();

private:
    ItemType    m_Type;
    BuffTarget  m_BuffType;
    Timer*      m_Timer = nullptr;
};

