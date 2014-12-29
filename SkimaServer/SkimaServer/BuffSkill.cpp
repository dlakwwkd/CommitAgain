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
    MoveSpeedBonus(5000, Reduce(300.0f));
}

void BuffSkill::ShieldBuff()
{
    ShieldBonus(300);
    m_ShieldOn = true;
}

void BuffSkill::ShieldDestroy()
{
    ShieldBonusEnd();
    m_ShieldOn = false;
}

