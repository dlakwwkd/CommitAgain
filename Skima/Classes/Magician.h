#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Vec2 createPos, float scale);
    virtual ~Magician();

public:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();
    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);

};

