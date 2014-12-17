#pragma once
#include "MapObject.h"
class MoveRock : public MapObject
{
public:
    MoveRock(Player* owner, const b2Vec2& pos);
    virtual ~MoveRock();
};

