#pragma once
#include "Unit.h"
class MapObject :
    public Unit
{
public:
    MapObject();
    ~MapObject();

protected:
    b2Vec2 m_Pos;
};

