#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Player* owner, b2Vec2 pos, float scale);
    virtual ~Magician();
    
    virtual void    UseSkill(SkillType skillType, SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
    virtual void    Extinction(){}
};

