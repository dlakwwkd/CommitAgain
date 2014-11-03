#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Unit(pos);
	auto client = GClientManager->GetClient(m_PlayerID);

	Sleep(3000);
	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetUnitType(), m_Hero->GetCurrentPos());
}

void Player::UnitMove()
{
	if (m_Hero->GetCurrentPos() == m_Hero->GetTargetPos())
	{
		m_Hero->SetIsMove(false);
		return;
	}
	m_Hero->SetCurrentPos(m_Hero->GetCurrentPos() + m_Hero->GetAverageMove());
}

void Player::SetAverageMove(b2Vec2 targetPos)
{
	m_Hero->SetIsMove(true);
	b2Vec2 averageMove;
	averageMove.x = (targetPos.x - m_Hero->GetCurrentPos().x) / 10 * m_Hero->GetSpeed();
	averageMove.y = (targetPos.y - m_Hero->GetCurrentPos().y) / 10 * m_Hero->GetSpeed();
	m_Hero->SetAverageMove(averageMove);
}

