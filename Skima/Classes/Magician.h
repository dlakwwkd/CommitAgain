#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Vec2 createPos, float scale);
    virtual ~Magician();

public:
    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);
    virtual void    HeroUnHide(Vec2 heroPos);

private:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();

};

