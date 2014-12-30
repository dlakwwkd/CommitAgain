#pragma once
#include "Unit.h"
class MapObject : public Unit
{
public:
    MapObject();
    virtual ~MapObject();

    void MapObjectBreak();

    virtual void    SetMoveMotionToCache() = 0;
    virtual void    SetMoveMotionByDir() = 0;
};

