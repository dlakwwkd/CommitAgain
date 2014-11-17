#pragma once
#include "Unit.h"
#include "Skill.h"
class Hero : public Unit
{
public:
	Hero();
	Hero(int playerId, int unitId, HeroType heroType, b2Vec2 pos);
	virtual~Hero();

	HeroType			GetHeroType(){ return m_HeroType; }

	virtual void		UnitMove();
	virtual void		BeginCrashed() { m_State->Crashed(this); }
	virtual void		Crashing(bool isCrashing) {}
	//virtual void		UnitCrashed(bool isCrashed);
	virtual void		UseSkill(SkillKey skillKey,b2Vec2 heroPos, b2Vec2 targetPos);
	
protected:
	int			m_SkillID;
	HeroType    m_HeroType;

	Skill*		m_Qskill;
	Skill*		m_Wskill;
	Skill*		m_Eskill;
	Skill*		m_Rskill;

};

