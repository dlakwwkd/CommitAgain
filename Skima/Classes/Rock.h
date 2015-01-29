#pragma once
#include "MapObject.h"
class Rock : public MapObject
{
public:
    Rock(int id, Vec2 pos);
    virtual ~Rock();

private:
    virtual void SetMoveMotionToCache(){}
    virtual void SetMoveMotionByDir(){}
};

