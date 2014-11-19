#pragma once
#include "Skill.h"

USING_NS_CC;

class FireballMissile;

class FireballSkill :
	public Skill
{
public:
	FireballSkill();
	~FireballSkill();

public:
	void SkillCast(Point heroPos, Point targetPos, int missileID);
	
private:
	FireballMissile* m_Missile;
};

