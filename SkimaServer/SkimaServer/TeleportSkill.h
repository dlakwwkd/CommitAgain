#pragma once
#include "Skill.h"
class TeleportSkill : public Skill
{
public:
    TeleportSkill(Player* owner);
    virtual~TeleportSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
};

