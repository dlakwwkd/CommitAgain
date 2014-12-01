#pragma once
#include "C:\CommitAgain\Skima\Classes\Skill.h"
class TeleportSkill :	public Skill
{
public:
	TeleportSkill();
	TeleportSkill(Hero* hero);

	~TeleportSkill();

public:
	virtual void SkillReady();
	virtual void SkillEnd();
};

