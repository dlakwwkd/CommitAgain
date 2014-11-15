#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"

class b2World;

class Unit
{
public:
	Unit(int playerId, b2Vec2 pos);
	Unit();
	~Unit();

public:
	int			GetUnitID(){ return m_UnitID; }
	void		SetUnitHp(int Hp){ m_Hp = Hp; }
	int			GetUnitHp(){ return m_Hp; }
	UnitType	GetUnitType(){ return m_Type; }
	void		SetSpeed(float speed){ m_Speed = speed; }
	float		GetSpeed(){ return m_Speed; }
	void		SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	b2Vec2		GetTargetPos(){ return m_TargetPos; }
	b2Body*		GetBody(){ return m_Body; }



protected:
	int			m_UnitID; 
	int			m_Hp;
	float		m_Speed; 
	UnitType	m_Type; 
	b2Vec2		m_TargetPos; 
	b2Body*		m_Body; 


};

