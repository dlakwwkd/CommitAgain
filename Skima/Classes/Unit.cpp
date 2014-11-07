#include "Unit.h"


Unit::Unit(const std::string& filename, Point createPos, float scale, GameMode gameMode)
{
	m_Speed = 100.0f;
	m_MoveMode = false;

	auto sprite = Sprite::create(filename);
	sprite->setPosition(createPos);
	sprite->setScale(scale);

	m_Sprite = sprite;

	switch (gameMode)
	{
	case SINGLE:
	{
		auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // 밀도, 탄성력, 마찰력

		PhysicsBody* body = nullptr;
		body = PhysicsBody::createCircle(sprite->getContentSize().width*(scale / 2), material);

		body->setMass(1.0f);
		body->setLinearDamping(3);
		body->setRotationEnable(false);

		sprite->setPhysicsBody(body);
		m_Body = body;
		break;
	}
	case MULTI:
		break;
	}

	m_MoveState = m_StandbyState = new StandbyState();
	m_MovingState = new MovingState();
	m_CrashedState = new CrashedState();
}

Unit::~Unit()
{
	delete m_StandbyState;
	delete m_MovingState;
	delete m_CrashedState;
}



void Unit::MoveTargeting(Point p)
{
	m_MoveMode		= true;
	m_MovePosition	= p;
}

void Unit::Move(GameMode gameMode)
{
	switch (gameMode)
	{
	case SINGLE:	MoveS();	break;
	case MULTI:		MoveM();	break;
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	게임 모드에 따라 나뉘는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void Unit::MoveS()
{
	if (m_MoveMode)
	{
		if (!(m_Body->getPosition().x < m_MovePosition.x - 5 ||
			m_Body->getPosition().y < m_MovePosition.y - 5 ||
			m_Body->getPosition().x > m_MovePosition.x + 5 ||
			m_Body->getPosition().y > m_MovePosition.y + 5))
		{
			m_MoveMode = false;
			m_Body->setVelocity(Vect::ZERO);
			return;
		}

		auto direction = m_MovePosition - m_Body->getPosition();
		auto temp = abs(direction.x) + abs(direction.y);

		direction *= m_Speed / temp;

		m_Body->applyImpulse(direction);
	}
}

void Unit::MoveM()
{
	if (m_MoveMode)
	{
		if (!(m_Body->getPosition().x < m_MovePosition.x - 5 ||
			m_Body->getPosition().y < m_MovePosition.y - 5 ||
			m_Body->getPosition().x > m_MovePosition.x + 5 ||
			m_Body->getPosition().y > m_MovePosition.y + 5))
		{
			m_MoveMode = false;
			m_Body->setVelocity(Vect::ZERO);
			return;
		}

		auto direction = m_MovePosition - m_Body->getPosition();
		auto temp = abs(direction.x) + abs(direction.y);

		direction *= m_Speed / temp;

		m_Body->applyImpulse(direction);
	}
}



///////////////////////////////////////////////////////////////////////////
/*
	상태 패턴 함수들
*/
///////////////////////////////////////////////////////////////////////////
void Unit::TryMove()
{
	m_MoveState->TryMove(this);
}
void Unit::EndMove()
{
	m_MoveState->EndMove(this);
}

void Unit::Crashed()
{
	m_MoveState->Crashed(this);

}
void Unit::EndCrashed()
{
	m_MoveState->EndCrash(this);
}


