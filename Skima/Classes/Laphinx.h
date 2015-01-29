#pragma once
#include "Hero.h"
class Laphinx : public Hero
{
public:
    Laphinx(Vec2 createPos, float scale);
    virtual ~Laphinx();

    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);
private:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();
};

