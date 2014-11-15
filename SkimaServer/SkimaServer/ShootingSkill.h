#pragma once
#include "Skill.h"
class ShootingSkill :
	public Skill
{
public:
	ShootingSkill();
	virtual ~ShootingSkill();

protected:
	virtual void Shoot();

};

