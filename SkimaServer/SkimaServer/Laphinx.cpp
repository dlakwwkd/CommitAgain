﻿#include "stdafx.h"
#include "Laphinx.h"
#include "GameManager.h"
#include "Skill.h"
#include "SwipeSKill.h"
#include "HideSkill.h"
#include "ClientSession.h"
#include "Player.h"

Laphinx::Laphinx(Player* owner, const b2Vec2& pos, float scale)
{
    SetDynamicBody(owner, HERO_LAPHINX, pos, scale);
    m_Hp = m_MaxHp = 1000;
    m_Speed = REDUCE(360);
    m_Damage = 80;
    m_SkillList[SKILL_Q] = new HideSkill(m_Owner);
//     m_SkillList[SKILL_W] = new IceballSkill(m_Owner, circle.m_radius);
    m_SkillList[SKILL_E] = new SwipeSkill(m_Owner);
}


Laphinx::~Laphinx()
{
}

void Laphinx::UnHide()
{
    if (m_IsHidden == false)
    {
        return;
    }

    else
    {
        auto client = m_Owner->GetClient();
        m_Body->SetAwake(false);
        m_IsHidden = false;
        this->EndMove();
        client->UnHideBroadCast(m_UnitID, m_Body->GetPosition());
    }
}
