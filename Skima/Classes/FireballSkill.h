#pragma once
#include "Skill.h"
class FireballMissile;
class Hero;

class FireballSkill : public Skill
{
public:
	FireballSkill();
	FireballSkill(Hero* hero);
	virtual ~FireballSkill();

public:
	//void SkillCast(Point heroPos, Point targetPos, int missileID);
	virtual void SkillReady();
	virtual void SkillEnd();
	
};

