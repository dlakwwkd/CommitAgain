#pragma once
#include "Hero.h"
class Jupiter : public Hero
{
public:
    Jupiter(Player* owner, b2Vec2 pos, float scale);
	virtual ~Jupiter();

	virtual void Extinction(){}
};

