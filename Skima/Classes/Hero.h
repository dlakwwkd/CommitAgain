#pragma once
#include "Unit.h"
class Skill;
class Buff;

class Hero : public Unit
{
public:
    Hero();
    virtual ~Hero();

    Vec2            GetHeroPos() { return m_CenterSprite->getPosition(); }
    Sprite*         GetArrow() { return m_Arrow; }
    Sprite*         GetSkillRange(){ return m_SkillRange; }
    Sprite*         GetNearSkillRange(){ return m_NearSkillRange; }
    HeroType        GetHeroType(){ return m_HeroType; }

    Skill*          GetSkill(SkillKey key);
    int             GetSkillCoolTime(SkillKey key);
    Buff*           GetBuff() { return m_Buff; }
    bool            GetSkillCanUse(SkillKey key);
    void			SetSkillCanUse(SkillKey key, bool isUse);

    void			SkillCast(SkillKey key, Vec2 recvPos, Vec2 targetPos);
    void			SkillReady(SkillKey key);
    void			SkillEnd(SkillKey key);

    void            SetSkillSprite();

    virtual void    SetMoveMotionByDir()				= 0;
    virtual void    SetSkillMotionByDir(SkillKey key)	= 0;
protected:
    virtual void    SetMoveMotionToCache()              = 0;
    virtual void    SetSkillMotionToCache()             = 0;

protected:
    std::map<SkillKey, Skill*>  m_SkillList;
    HeroType                    m_HeroType;
    Sprite*                     m_Arrow	= nullptr;
    Sprite*                     m_SkillRange = nullptr;
    Sprite*                     m_NearSkillRange = nullptr;
	Label*						m_PlayerName = nullptr;
    bool                        m_IsPerforming;
    Buff*                       m_Buff;
};

