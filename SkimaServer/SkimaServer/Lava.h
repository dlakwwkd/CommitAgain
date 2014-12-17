#pragma once
#include "Terrain.h"
class Lava :
    public Terrain
{
public:
    Lava(b2Vec2 createPos);
    virtual ~Lava();
};

