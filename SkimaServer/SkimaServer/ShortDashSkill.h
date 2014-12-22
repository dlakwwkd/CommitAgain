#pragma once
#include "Skill.h"
class ShortDashSkill : public Skill
{
public:
    ShortDashSkill(Player* owner);
    virtual ~ShortDashSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);

};

