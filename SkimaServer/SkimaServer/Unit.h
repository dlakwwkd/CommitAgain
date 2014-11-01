#pragma once
#include "Vec2.h"

enum UnitType
{
	TYPE_NONE
};

class Unit
{
public:
	Unit();
	~Unit();

public:
	Point		GetCurrentPos(){ return mCurrentPos; }
	void		SetCurrentPos();
	Point		GetTargetPos(){ return mTargetPos; }
	void		SetTargetPos();
	UnitType	GetUnitType(){ return mType; }

private:
	Point		mCurrentPos;
	Point		mTargetPos;
	UnitType	mType;
	int			speed;
};

