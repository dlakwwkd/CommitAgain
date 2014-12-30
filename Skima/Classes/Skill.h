﻿#pragma once
#include "PacketType.h"
#include "Enums.h"
class Hero;

USING_NS_CC;

class Skill
{
public:
    Skill();
    virtual ~Skill();

    int             GetCoolTime() { return m_CoolTime; }
    bool            GetCanUse() { return m_CanUse; }
    Sprite*         GetSprite() { return m_Sprite; }
    void            SetCanUse(bool isUse) { m_CanUse = isUse; }

    virtual void	SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos) = 0;
    virtual void	SkillCast(Vec2 heroPos, Vec2 targetPos)         = 0;
    virtual void    SkillReady()							        = 0;
    virtual void    SkillEnd()								        = 0;

    void            SetHeroPerforming(bool isPerforming);
    Direction       GenerateSkillDirection(Vec2 targetPos, Vec2 curPos);

    void            CreateSprite(const char* image, Vec2 scale, Vec2 anchor);

protected:
    Hero*			m_Owner = nullptr;
    int				m_CoolTime = 0;
    bool			m_CanUse = false;
    Sprite*         m_Sprite = nullptr;
};

