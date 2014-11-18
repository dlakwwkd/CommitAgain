#pragma once
#include "Unit.h"
#include "Skill.h"
#include <map>

typedef std::map<SkillKey, Skill*> SkillList;

class Hero : public Unit
{
public:
	Hero();
	Hero(int playerId, int unitId, HeroType heroType, b2Vec2 pos);
	~Hero(); ///# 가상 소멸자~~~ 쫌!

	HeroType			GetHeroType(){ return m_HeroType; }
	const SkillList&	GetSkillList(){ return m_SkillList; } ///# 내부 컬렉션을 외부에 참조를 던지는 구조는 NAVER!

	void				UnitMove();
	virtual void		UseSkill(SkillKey skillKey,b2Vec2 heroPos, b2Vec2 targetPos);
	
protected:
	int			m_SkillID;
	HeroType    m_HeroType;

	SkillList	m_SkillList;
};

