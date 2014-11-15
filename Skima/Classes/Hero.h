#pragma once
#include "Unit.h"
class Hero :
	public Unit
{
public:
	Hero();
	virtual ~Hero();

protected:
	HeroType m_HeroType;
};

