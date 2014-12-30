#pragma once
#include "MapObject.h"
class Lava : public MapObject
{
public:
    Lava(int id, Vec2 pos);
    virtual ~Lava();

    virtual void    SetMoveMotionToCache();
    virtual void    SetMoveMotionByDir();
};

