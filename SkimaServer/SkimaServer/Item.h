#pragma once
#include "Unit.h"
class Mob;

class Item : public Unit
{
public:
    Item(Mob* mob, BuffTarget type);
    virtual ~Item();

    BuffTarget GetBuffTarget() { return m_BuffType; }

private:
    BuffTarget m_BuffType;
};

