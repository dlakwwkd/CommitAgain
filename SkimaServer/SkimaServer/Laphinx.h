﻿#pragma once
#include "Hero.h"
class Laphinx : public Hero
{
public:
    Laphinx(Player* owner, b2Vec2 pos, float scale);
    virtual ~Laphinx();
    
    virtual void Extinction(){}
};
