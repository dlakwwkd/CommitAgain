#pragma once
#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class Unit
{
public:
	Unit(const std::string& filename, BodyShape shape, Point createPos, float scale);

	Sprite*			getSprite(){ return m_Sprite; }
	PhysicsBody*	getBody(){ return m_Body; }

	void			moveTargeting(Point p);
	void			movement();

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;

	std::string		m_Name;
	int				m_MaxHp;
	int				m_MaxMp;
	int				m_Hp;
	int				m_Mp;
	float			m_Speed;

	Point			m_MovePosition;
	bool			m_MoveMode;
};