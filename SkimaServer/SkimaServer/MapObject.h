#pragma once
#include "Unit.h"
class MapObject : public Unit
{
public:
    MapObject();
    virtual ~MapObject();

    b2Vec2 GetPos() { return m_Pos; }

protected:
    b2Vec2 m_Pos;
};

