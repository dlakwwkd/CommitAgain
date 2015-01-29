#pragma once
#include "Hero.h"
class Jupiter : public Hero
{
public:
    Jupiter(Vec2 createPos, float scale);
    virtual ~Jupiter();

    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);
private:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();
};

