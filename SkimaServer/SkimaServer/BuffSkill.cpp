#include "stdafx.h"
#include "BuffSkill.h"
#include "Player.h"


BuffSkill::BuffSkill(Player* owner)
{
    m_Owner = owner;
}


BuffSkill::~BuffSkill()
{
}

void BuffSkill::SpeedBuff()
{
    MoveSpeedBonus(3000, Reduce(100.0f));
}

void BuffSkill::ShieldBuff()
{
    ShieldBonus(500);
    m_ShieldOn = true;
}

void BuffSkill::ShieldDestroy()
{
    ShieldBonusEnd();
    m_ShieldOn = false;
}

