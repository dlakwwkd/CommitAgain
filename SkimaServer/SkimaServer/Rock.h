#pragma once
#include "MapObject.h"
class Rock :
    public MapObject
{
public:
    Rock(Player* owner, b2Vec2 pos);
    ~Rock();
};

