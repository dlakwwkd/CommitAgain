#pragma once
#include "Unit.h"
class Item :	public Unit
{
public:
    Item(Vec2 createPos, float scale, BuffTarget buffType);
    virtual ~Item();
};

