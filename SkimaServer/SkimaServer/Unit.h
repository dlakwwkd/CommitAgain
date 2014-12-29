#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"
class Player;
class BuffSkill;

#define DAMPING 5.0f
#define DEF_SCALE 15.0f

class Unit
{
public:
    Unit();
    virtual ~Unit();

public:
    void            SetType(int type){ m_UnitID += type; }
    void	        SetDamage(int damage) { m_Damage = damage; }
    void            SetMaxHp(int MaxHp){ m_MaxHp = MaxHp; }
    void            SetHp(int Hp){ m_Hp = Hp; }
    void            SetSpeed(float speed){ m_Speed = speed; }
    void            SetShield(int shield){ m_Shield = shield; }
    void			SetTargetPos(const b2Vec2& targetPos){ m_TargetPos = targetPos; }

    Player*         GetOwner(){ return m_Owner; }
    int             GetUnitID(){ return m_UnitID; }
    int             GetDamage(){ return m_Damage; }
    int             GetMaxHp(){ return m_MaxHp; }
    int             GetHp(){ return m_Hp; }
    float           GetSpeed(){ return m_Speed; }
    int             GetShield(){ return m_Shield; }
    const b2Vec2&	GetTargetPos(){ return m_TargetPos; }
    b2Body*         GetBody(){ return m_Body; }
    void            InitBody(){ m_Body = nullptr; }

    void			SetDynamicBody(Player* owner, int type, const b2Vec2& initPos, float scale);
    void			SetStaticBody(Player* owner, int type, const b2Vec2& initPos, const b2Vec2& scale);

    void            Moving();
    void            ReachCheck();
    void            Crashing();
    void            CurPosSync();

    void            Damaged(int damage);
    virtual void    Dead();
    void            UseBuff(BuffTarget type);

    void			TryMove(const b2Vec2& currentPos, const b2Vec2& targetPos);
    void            Crashed(Unit* contactUnit);
    void            EndMove(){ m_State->EndMove(this); }
    void            EndCrash(){ m_State->EndCrash(this); }
    void            Movement(){ m_State->Movement(this); }

    bool            GetUnitHiddenState(){ return m_IsHidden; }
    void            SetUnitHiddenState(bool hidden){ m_IsHidden = hidden; }

    void            SetState(MoveState* state){ m_State = state; }
    MoveState*      GetState(){ return (MoveState*)m_State; }
    MoveState*      GetStandbyState(){ return (MoveState*)m_StandbyState; }
    MoveState*      GetMovingState(){ return (MoveState*)m_MovingState; }
    MoveState*      GetCrashedState(){ return (MoveState*)m_CrashedState; }

protected:
    Player*     m_Owner			= nullptr;
    int         m_UnitID		= -1;
    int         m_MaxHp			= 0;
    int         m_Hp			= 0;
    int         m_Shield        = 0;
    int         m_Damage		= 0;
    float       m_Speed			= 0; 
    bool        m_InUse			= false;
    bool        m_IsHidden      = false;
    b2Vec2      m_TargetPos		= { 0, 0 };
    b2Body*     m_Body			= nullptr;
    BuffSkill*  m_Buff          = nullptr;
    MoveState*  m_State			= nullptr;
    MoveState*  m_StandbyState	= nullptr;
    MoveState*  m_MovingState	= nullptr;
    MoveState*  m_CrashedState	= nullptr;
};


