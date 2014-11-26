#pragma once
#include "Skill.h"

USING_NS_CC;

class IceballMissile;
class Hero;

class IceballSkill : public Skill
{
public:
	IceballSkill();
	IceballSkill(Hero* hero);
	virtual ~IceballSkill();

public:
	//void SkillCast(Point heroPos, Point targetPos, int missileID);
	virtual void SkillReady();
	virtual void SkillEnd();
};

