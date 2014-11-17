#pragma once
#include "Skill.h"

class FireballMissile;

class FireballSkill :
	public Skill
{
public:
	FireballSkill();
	~FireballSkill();

public:
	void SkillCast(Point heroPos, Point targetPos);
	
private:
	FireballMissile* m_Missile;
};

