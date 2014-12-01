#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"

#define DAMPING 5.0f
#define DEF_SCALE 15.0f

class Unit
{
public:
    Unit();
    virtual ~Unit();

public:
    void            SetType(int type){ m_UnitID += type; }
    void			SetMaxHp(int MaxHp){ m_MaxHp = MaxHp; }
    void			SetUnitHp(int Hp){ m_Hp = Hp; }
    void			SetSpeed(float speed){ m_Speed = speed; }
    void			SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
    void			SetContectState(bool state){ m_Contacting = state; }

    int				GetPlayerID(){ return m_PlayerID; }
    int				GetUnitID(){ return m_UnitID; }
    int				GetMaxHp(){ return m_MaxHp; }
    int				GetUnitHp(){ return m_Hp; }
    int				GetUnitDamage(){ return m_Damage; }
    float			GetSpeed(){ return m_Speed; }
    bool			GetContectState(){ return m_Contacting; }
    b2Vec2			GetTargetPos(){ return m_TargetPos; }
    b2Body*			GetBody(){ return m_Body; }
    void			InitBody(){ m_Body = nullptr; }

    void			Moving();
    void			Crashing(bool isCrashing);
    void			IamDead();
    virtual void    Extinction(){}

    void			TryMove(b2Vec2 currentPos, b2Vec2 targetPos);
    void			Crashed(){ m_State->Crashed(this); }
    void			EndMove(){ m_State->EndMove(this); }
    void			EndCrash(){ m_State->EndCrash(this); }
    void			Movement(){ m_State->Movement(this); }

    void			SetState(MoveState* state){ m_State = state; }
    MoveState*		GetState(){ return (MoveState*)m_State; }
    MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
    MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
    MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }

protected:
    int			m_PlayerID;
    int			m_UnitID; 
    int			m_MaxHp;
    int			m_Hp;
    int			m_Damage;
    float		m_Speed; 
    bool		m_InUse;
    bool		m_Contacting;
    b2Vec2		m_TargetPos; 
    b2Body*		m_Body; 
    
    MoveState*	m_State;
    MoveState*	m_StandbyState;
    MoveState*	m_MovingState;
    MoveState*	m_CrashedState;

    friend class ObjectManager;
};


