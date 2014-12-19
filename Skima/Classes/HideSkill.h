#pragma once
#include "Skill.h"
class HideSkill : public Skill
{
public:
    HideSkill();
    HideSkill(Hero* hero);
    virtual ~HideSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();

    void SetSpriteOpacity(Sprite* sprite, float opacity);

private:
    int m_HiddenTime;
};

