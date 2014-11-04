#pragma once
#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MultiUnit
{
public:
	MultiUnit(const std::string& filename, BodyShape shape, Point createPos, float scale);

	Sprite*			GetSprite(){ return m_Sprite; }
	PhysicsBody*	GetBody(){ return m_Body; }

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	int				GetUnitID(){ return m_UnitID; }
	void			MoveTargeting(Point p);
	void			Movement();

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;

	std::string		m_Name;
	int				m_PlayerID;
	int				m_UnitID;
	int				m_MaxHp;
	int				m_MaxMp;
	int				m_Hp;
	int				m_Mp;
	float			m_Speed;

	Point			m_MovePosition;
	bool			m_MoveMode;
};