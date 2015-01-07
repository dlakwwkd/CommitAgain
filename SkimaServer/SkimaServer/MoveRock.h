#pragma once
#include "MapObject.h"
#include "ObjectPool.h"
class MoveRock : public MapObject, public ObjectPool<MoveRock>
{
public:
    MoveRock(Player* owner, const b2Vec2& pos);
    virtual ~MoveRock();
};

