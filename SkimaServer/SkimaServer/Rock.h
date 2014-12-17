#pragma once
#include "MapObject.h"
class Rock :
    public MapObject
{
public:
    Rock(Player* owner, const b2Vec2& pos);
    virtual ~Rock();
};

