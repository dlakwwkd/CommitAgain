#pragma once
#include "Unit.h"
class MapObject :
    public Unit
{
public:
    MapObject();
    ~MapObject();

private:
    b2Vec2 m_Pos;
};

