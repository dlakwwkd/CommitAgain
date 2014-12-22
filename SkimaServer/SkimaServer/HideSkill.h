#pragma once
#include "Skill.h"
class HideSkill : public Skill
{
public:
    HideSkill(Player* owner);
    virtual ~HideSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);

};

