#pragma once
#include "Skill.h"
class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void    SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos){}

protected:

};

