#pragma once
#include "Skill.h"
class FlashSkill : public Skill
{
public:
    FlashSkill();
    FlashSkill(Player* owner);
    virtual ~FlashSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);

};

