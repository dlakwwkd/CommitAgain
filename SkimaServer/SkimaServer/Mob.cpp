#include "stdafx.h"
#include "Mob.h"
#include "Scheduler.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"



Mob::Mob()
{
	static int makeId = 0;
	m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_MOB);
}


Mob::~Mob()
{
}

void Mob::ChaseEnemy()
{
    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&Mob::Chasing, this);
    game->InfiniteTimer(1000, func);
}

void Mob::Chasing()
{
    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    game->Targeting(this);

    auto currentPos = m_Body->GetPosition();
    auto displacement = m_TargetPos - currentPos;
    displacement.Normalize();
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    m_Owner->GetClient()->TryMoveBroadCast(m_UnitID, currentPos, m_TargetPos);
    m_State->TryMove(this);
}
