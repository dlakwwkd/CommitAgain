#pragma once
#include "Unit.h"
class MapObject : public Unit
{
public:
    MapObject();
    virtual ~MapObject();

    void MapObjectBreak();

private:
    virtual void SetMoveMotionToCache(){}
    virtual void SetMoveMotionByDir(){}
};

