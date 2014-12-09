#pragma once
#include "Hero.h"
class Jupiter : public Hero
{
public:
    Jupiter(Player* owner, b2Vec2 pos, float scale);
	virtual ~Jupiter();

	virtual void    UseSkill(SkillType skillType, SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
	virtual void    Extinction(){}
};

