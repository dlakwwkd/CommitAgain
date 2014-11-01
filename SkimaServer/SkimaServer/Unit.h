#pragma once
#include "..\..\PacketType.h"

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
	N_Point		GetCurrentPos(){ return mCurrentPos; }
	void		SetCurrentPos();
	N_Point		GetTargetPos(){ return mTargetPos; }
	void		SetTargetPos();
	UnitType	GetUnitType(){ return mType; }

private:
	N_Point		mCurrentPos;
	N_Point		mTargetPos;
	UnitType	mType;
	int			speed;
};

