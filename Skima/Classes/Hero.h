#pragma once
#include "Unit.h"
class Hero :
	public Unit
{
public:
	Hero();
	virtual ~Hero();

	HeroType GetHeroType(){ return m_HeroType; }

protected:
	HeroType m_HeroType;
};

