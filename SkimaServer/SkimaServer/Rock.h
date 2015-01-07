#pragma once
#include "MapObject.h"
#include "ObjectPool.h"
class Rock : public MapObject, public ObjectPool<Rock>
{
public:
    Rock(Player* owner, const b2Vec2& pos);
    virtual ~Rock();
};

