#pragma once
#include "cocos2d.h"
#include "Enums.h"
#include "../../PacketType.h"

USING_NS_CC;

class Unit
{
public:
	Unit(const std::string& filename, Point createPos, float scale, SINGLE_MODE_FUNC);

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }

	void			MoveTargeting(Point p);
	void			Movement(SINGLE_MODE_FUNC);

public:
	Unit(const std::string& filename, Point createPos, float scale, MULTI_MODE_FUNC);

	PhysicsBody*	GetBody(){ return m_Body; }

	void			Movement(MULTI_MODE_FUNC);

protected:
	UnitType		m_UnitType;
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

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;

};