#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Player* owner, const b2Vec2& pos, float scale);
    virtual ~Magician();
    
    virtual void Extinction(){}
};

