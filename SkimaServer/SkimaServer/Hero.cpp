#include "stdafx.h"
#include "Hero.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"

Hero::Hero()
{
	m_UnitType = UNIT_HERO;
	m_Speed = 10.0f;
	m_TargetPos = { 0, 0 };
}

Hero::Hero(int playerId, int unitId, HeroType heroType, b2Vec2 pos)
{
	
}


Hero::~Hero()
{
}



void Hero::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
	//각각의 캐릭터의 useskill만 호출 (검증필요..)
}
