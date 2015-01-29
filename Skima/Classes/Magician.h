#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Vec2 createPos, float scale);
    virtual ~Magician();

    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);
private:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();
};

