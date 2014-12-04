#pragma once
#include "Enums.h"
#include "PacketType.h"
#include "FSM.h"

USING_NS_CC;
typedef std::map<Direction, Animation*> MoveMotion;
class Skill;

class Unit
{
public:
    Unit();
    Unit(const std::string& filename, Vec2 createPos, float scale);
    virtual ~Unit();

    void            SetType(int type){ m_UnitID = SET_SIDE_TYPE(m_UnitID, type); }
    void            SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
    void            SetUnitID(int unitID){ m_UnitID = unitID; }
    void            SetTargetPos(Vec2 pos){ m_TargetPos = pos; }
    void            SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
    int             GetUnitPlayerID(){ return m_PlayerID; }
    int             GetUnitID(){ return m_UnitID; }
    Sprite*         GetSprite(){ return m_Sprite; }
    Sprite*         GetHpBar(){ return m_HpBar; }
    float           GetMaxHp(){ return m_MaxHp; }
    float           GetCurHp(){ return m_CurHp; }
    Vec2            GetMoveTargetPos(){ return m_TargetPos; }

    MoveState*      GetMoveState(){ return m_MoveState; }
    MoveState*      GetStandbyState(){ return (MoveState*)m_StandbyState; }
    MoveState*      GetMovingState(){ return (MoveState*)m_MovingState; }
    MoveState*      GetCrashedState(){ return (MoveState*)m_CrashedState; }
    void            TryMove(){ m_MoveState->TryMove(this); }
    void            EndMove(){ m_MoveState->EndMove(this); }
    void            Crashed(){ m_MoveState->Crashed(this); }
    void            EndCrash(){ m_MoveState->EndCrash(this); }
    void            Movement(){ m_MoveState->Movement(this); }

    void            SetHp(int curHp);
    void            SetHpBar();
    void            UpdateHpBar();

    void            Move();
    void            Crash();

public:
    PhysicsBody*    GetBody(){ return m_Body; }

protected:
    void            MoveS();
    void            MoveM();
    void            CrashS();
    void            CrashM();


protected:
    MoveState*      m_MoveState;
    MoveState*      m_StandbyState;
    MoveState*      m_MovingState;
    MoveState*      m_CrashedState;

protected:
    MoveMotion      m_MoveMotionByDir;
    std::string     m_Name;
    int             m_PlayerID;
    int             m_UnitID;
    float           m_MaxHp;
    float           m_CurHp;
    float           m_Speed;
    bool            m_InUse;

    Vec2            m_TargetPos;

protected:
    Sprite*         m_Sprite;
    Sprite*         m_HpBar;
    PhysicsBody*    m_Body;


    friend class ObjectManager;
};