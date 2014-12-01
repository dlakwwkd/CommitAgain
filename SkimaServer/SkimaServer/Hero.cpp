#include "stdafx.h"
#include "Hero.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"

Hero::Hero()
{
    m_UnitID = SET_MAIN_TYPE(m_UnitID, UNIT_HERO);
}

Hero::~Hero()
{
}

void Hero::UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos)
{
    //각각의 캐릭터의 useskill만 호출 
}
