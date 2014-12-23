#pragma once
#include "Skill.h"

class Hero;
class MeteorSkill : public Skill
{
public:
    MeteorSkill();
    MeteorSkill(Hero* hero);
    virtual ~MeteorSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();

    void         MakeMeteor(Vec2 targetpos);

public:
    Sprite*      m_CautionSprite;
};

