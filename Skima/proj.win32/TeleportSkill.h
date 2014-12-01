#pragma once
#include "Skill.h"
class TeleportSkill :	public Skill
{
public:
	TeleportSkill();
	TeleportSkill(Hero* hero);

	~TeleportSkill();

public:
	virtual void SkillReady();
	virtual void SkillEnd();

private:
	Sprite*	m_RangeShape;
};

