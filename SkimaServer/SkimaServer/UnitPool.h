#pragma once
#include "Unit.h"
class UnitPool : public Unit
{
public:
	UnitPool();
	virtual ~UnitPool();
	virtual void	Extinction(){}

	void			SetTargetPos(const b2Vec2& targetPos){ m_TargetPos = targetPos; }
	void	        SetHp(int hp) { m_Hp = hp; }
	void	        SetDamage(int damage) { m_Damage = damage; }
	void	        SetSpeed(float speed) { m_Speed = speed; }
	void	        SetRange(float range) { m_Range = range; }
	void	        SetLivetime(float livetime) { m_Livetime = livetime; }

protected:
	float			m_Range = 0.0f;
	float			m_Livetime = 0.0f;
};

