#include "stdafx.h"
#include "Magician.h"
#include "FireballSkill.h"

Magician::Magician()
{
}

Magician::Magician(int playerId, HeroType heroType, b2Vec2 pos)
{
	m_HeroType = HERO_MAGICIAN;

	m_Qskill = new FireballSkill(m_PlayerID);
}


Magician::~Magician()
{
}

void Magician::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
	//broadcast skill id , unit pos...
	//skill id == missile unit id
	switch (skillKey)
	{
	case SKILL_NONE:
		break;

	case SKILL_Q:
		m_Qskill->ShootSkill(m_UnitID,heroPos,targetPos);
		break;

	case SKILL_W:
		break;

	case SKILL_E:
		break;

	case SKILL_R:
		break;

	}
}
		
