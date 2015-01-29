﻿#pragma once
#include "Unit.h"
class Mob :	public Unit
{
public:
    Mob(Vec2 createPos, float scale, int hp, float speed);
    virtual ~Mob();

private:
    virtual void SetMoveMotionByDir();
    virtual void SetMoveMotionToCache();
};

