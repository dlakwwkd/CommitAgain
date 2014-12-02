#pragma once
#include "Unit.h"
class Skill;

class Hero : public Unit
{
public:
    Hero();
    virtual ~Hero();

    int             GetSkillCoolTime(SkillKey key);
    bool            GetSkillCanUse(SkillKey key);
    Vec2            GetHeroPos() { return m_Sprite->getPosition(); }
    Sprite*         GetArrow() { return m_Arrow; }
    Sprite*         GetSkillRange(){ return m_SkillRange; }
    Skill*          GetSkill(SkillKey key){ return m_SkillList[key]; }
    virtual void	SetMoveMotionByDir() = 0;
    void			SetSkillCanUse(SkillKey key, bool isUse);
    void			SkillCast(SkillKey key);
    void			SkillReady(SkillKey key);
    void			SkillEnd(SkillKey key);

protected:
    RepeatForever*  MakeAnimation(const char* format);
    Direction       CalcDirection(Vec2 displacement);

protected:
    std::map<SkillKey, Skill*>  m_SkillList;

    Sprite*                     m_Arrow;
    Sprite*                     m_SkillRange;
};

