#pragma once
#include "FieldType.h"
class LightningSkill : public FieldType
{
public:
    LightningSkill(Player* owner);
	virtual ~LightningSkill();

    virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);
};

