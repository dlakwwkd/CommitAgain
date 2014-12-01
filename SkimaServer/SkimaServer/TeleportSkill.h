#pragma once
#include "Skill.h"
class TeleportSkill : public Skill
{
public:
    TeleportSkill();
    TeleportSkill(int playerId);
    virtual~TeleportSkill();

    virtual void SkillCast(b2Vec2 heroPos, b2Vec2 targetPos);
};

