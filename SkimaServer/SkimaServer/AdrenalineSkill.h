#pragma once
#include "Skill.h"
class AdrenalineSkill : public Skill
{
public:
    AdrenalineSkill();
    AdrenalineSkill(Player* owner);
    virtual ~AdrenalineSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);

};

