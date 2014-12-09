#pragma once
#include "Unit.h"
class Skill;

class Hero : public Unit
{
public:
    Hero();
    virtual ~Hero();

    Vec2            GetHeroPos() { return m_Sprite->getPosition(); }
    Sprite*         GetArrow() { return m_Arrow; }
    Sprite*         GetSkillRange(){ return m_SkillRange; }

    Skill*          GetSkill(SkillKey key);
    int             GetSkillCoolTime(SkillKey key);
    bool            GetSkillCanUse(SkillKey key);
    void			SetSkillCanUse(SkillKey key, bool isUse);

    void			SkillCast(SkillKey key, Vec2 recvPos, Vec2 targetPos);
    void			SkillReady(SkillKey key);
    void			SkillEnd(SkillKey key);

    virtual void    SetMoveMotionToCache() = 0;
    virtual void    SetSkillMotionToCache() = 0;
    virtual void    SetMoveMotionByDir() = 0;
    virtual void    SetSkillMotionByDir(SkillKey key) = 0;

protected:
    RepeatForever*  MakeAnimation(const char* format, int size);
    Direction       CalcMoveDirection(Vec2 displacement);
    Direction       CalcSkillDirection(Vec2 displacement);

protected:
    std::map<SkillKey, Skill*>  m_SkillList;
    Sprite*                     m_Arrow;
    Sprite*                     m_SkillRange;
};

