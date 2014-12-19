#pragma once
#include "MapObject.h"
#include "GameManager.h"

class Lava :
    public MapObject
{
public:
    Lava(Player* owner, b2Vec2 createPos);
    virtual ~Lava();

private:
    Rect range;
};

