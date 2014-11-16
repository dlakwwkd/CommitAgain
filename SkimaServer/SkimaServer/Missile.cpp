#include "stdafx.h"
#include "Missile.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "GameManager.h"



Missile::Missile()
{

}

Missile::Missile(int playerId, int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{
	//todo
	//b2Vec2 direction = heroPos - targetPos;
	
	b2Vec2 initPos;//������ ����ؼ� �־��ֱ�
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(initPos.x,initPos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 10.0f / PTM_RATIO;
}


Missile::~Missile()
{
}

void Missile::MissileShoot()
{
	
	auto direction = m_TargetPos - m_Body->GetPosition();
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);
	//todo : �ڵ��߰��� �����ʿ�
}

void Missile::ConsumeLiveTime(float costTime)
{

}

void Missile::SetMissileInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
	//todo 

	//hoor pos�� target pos ������ͼ� �A�� ��� ������...
}
