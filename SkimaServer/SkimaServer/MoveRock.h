#pragma once
#include "MapObject.h"
class MoveRock :
    public MapObject
{
public:
    MoveRock(Player* owner, b2Vec2 pos);
    ~MoveRock();
};

