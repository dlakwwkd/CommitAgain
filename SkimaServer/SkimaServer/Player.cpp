#include "stdafx.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"


void Player::CreateHero(b2Vec2 pos)
{
	m_Hero = new Unit(pos);
	auto client = GClientManager->GetClient(m_PlayerID);

	Sleep(500);

	client->SendCreateHeroResult(m_Hero->GetUnitID(),m_Hero->GetUnitType(), m_Hero->GetCurrentPos());
}

void Player::UnitMove()
{
	if (!(m_Hero->GetCurrentPos().x < m_Hero->GetTargetPos().x - 5 ||
		m_Hero->GetCurrentPos().y < m_Hero->GetTargetPos().y - 5 ||
		m_Hero->GetCurrentPos().x > m_Hero->GetTargetPos().x + 5 ||
		m_Hero->GetCurrentPos().y > m_Hero->GetTargetPos().y + 5))
	{
		m_Hero->SetIsMove(false);
		return;
	}
	m_Hero->SetCurrentPos(m_Hero->GetCurrentPos() + m_Hero->GetAverageMove());
}

void Player::SetAverageMove(b2Vec2 targetPos)
{
	m_Hero->SetIsMove(true);

	auto direction = targetPos - m_Hero->GetCurrentPos();
	auto temp = abs(direction.x) + abs(direction.y);

	direction *= m_Hero->GetSpeed() / temp;
	
	m_Hero->SetAverageMove(direction);
}

