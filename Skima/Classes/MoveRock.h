#pragma once
#include "MapObject.h"
class MoveRock : public MapObject
{
public:
    MoveRock(int id, Vec2 pos);
    virtual ~MoveRock();

private:
    virtual void SetMoveMotionToCache(){}
    virtual void SetMoveMotionByDir(){}
};

