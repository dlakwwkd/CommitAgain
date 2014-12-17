#pragma once
#include "FieldType.h"
class LightningSkill : public FieldType
{
public:
    LightningSkill(Player* owner);
	virtual ~LightningSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
};

