#pragma once
#include "Hero.h"
class Jupiter : public Hero
{
public:
	Jupiter(Vec2 createPos, float scale);
	virtual ~Jupiter();

public:
	void			SetMoveMotionToCache();
	virtual void	SetMoveMotionByDir();
private:
};

