#include "Unit.h"


Unit::Unit(const std::string& filename, BodyShape shape, Point createPos, float scale)
{
	m_Speed		= 100.0f;
	m_MoveMode	= false;

	auto sprite = Sprite::create(filename);
	auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // ¹Ðµµ, Åº¼º·Â, ¸¶Âû·Â
	
	PhysicsBody* body = nullptr;
	switch (shape)
	{
	case CIRCLE:
		body = PhysicsBody::createCircle(sprite->getContentSize().width*(scale / 2), material);
		break;
	case BOX:
		body = PhysicsBody::createBox(Size(sprite->getContentSize().width * scale,
										sprite->getContentSize().height * scale), material);
		break;
	}

	body->setMass(1.0f);
	body->setLinearDamping(3);

	sprite->setPhysicsBody(body);
	body->setRotationEnable(false);
	sprite->setPosition(createPos);
	sprite->setScale(scale);

	m_Sprite	= sprite;
	m_Body		= body;
}

void Unit::MoveTargeting(Point p)
{
	m_MoveMode		= true;
	m_MovePosition	= p;
}

void Unit::Movement()
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
