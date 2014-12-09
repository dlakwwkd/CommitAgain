#pragma once
#include "MapObject.h"
class Rock :
    public MapObject
{
public:
    Rock(b2Vec2 pos);
    ~Rock();
};

