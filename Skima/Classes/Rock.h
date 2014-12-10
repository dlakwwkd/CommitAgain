#pragma once
#include "MapObject.h"
class Rock :
    public MapObject
{
public:
    Rock(int id, Vec2 pos);
    ~Rock();
};

