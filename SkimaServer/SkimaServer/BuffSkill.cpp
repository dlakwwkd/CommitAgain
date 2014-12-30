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

void BuffSkill::HpBuff()
{
    HpBonus(150);
}

void BuffSkill::DamageBuff()
{
    DamageBonus(2000, 1.5);
}

