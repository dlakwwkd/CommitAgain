#pragma once
#include "Hero.h"
#include "PacketType.h"

class Jupiter : public Hero
{
public:
    Jupiter(Vec2 createPos, float scale);
    virtual ~Jupiter();

public:
    virtual void    SetMoveMotionToCache();
    virtual void    SetSkillMotionToCache();
    virtual void    SetMoveMotionByDir();
    virtual void    SetSkillMotionByDir(SkillKey key);
private:
};

