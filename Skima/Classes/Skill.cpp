#include "pch.h"
#include "Skill.h"
#include "Hero.h"


Skill::Skill()
{
    m_CoolTime = 0;
    m_CanUse = true;
}

Skill::~Skill()
{
}

Direction Skill::GenerateSkillDirection(Vec2 targetPos, Vec2 curPos)
{
    Vec2 displacement = targetPos - curPos;
    float slope = displacement.y / displacement.x;

    if (displacement.x > 0)
    {
        if (slope >= 0) return Direction::NE;
        if (slope < 0)  return Direction::SE;
    }
    else if (displacement.x < 0)
    {
        if (slope >= 0) return Direction::SW;
        if (slope < 0)  return Direction::NW;
    }
    return Direction::SE;
}
