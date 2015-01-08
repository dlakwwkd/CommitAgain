#include "stdafx.h"
#include "FireWallSkill.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"

FireWallSkill::FireWallSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 32;
    m_Scale = Reduce(80.0f);
}


FireWallSkill::~FireWallSkill()
{
}

void FireWallSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TaretPos = targetPos;

    auto game = m_Owner->GetGame();
    Timer::Push(game, 50, 5, this, &FireWallSkill::DiagonalRadiation, 100, 4, 5);
    Timer::Push(game, 1000, 50, 6, this, &FireWallSkill::CrossRadiation, 100, 4, 6);
}
