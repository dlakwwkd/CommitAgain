#pragma once
#include "Hero.h"
class Jupiter : public Hero
{
public:
    Jupiter(Player* owner, const b2Vec2& pos, float scale);
	virtual ~Jupiter();

	virtual void Extinction(){}
};

