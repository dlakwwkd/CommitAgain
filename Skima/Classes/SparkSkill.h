#pragma once
#include "Skill.h"
class SparkSkill : public Skill
{
public:
	SparkSkill();
	SparkSkill(Hero* hero);
	virtual ~SparkSkill();

public:
	virtual void SkillReady();
	virtual void SkillEnd();
};

