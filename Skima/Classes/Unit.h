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
    void            SetAllSpriteVisible();
    int             GetUnitPlayerID(){ return m_PlayerID; }
    int             GetUnitID(){ return m_UnitID; }
    Sprite*         GetRealSprite(){ return m_RealSprite; }
    Sprite*         GetSprite(){ return m_Sprite; }
    Sprite*         GetMyHpBar(){ return m_MyHpBar; }
    Sprite*         GetOtherHpBar(){ return m_EnemyHpBar; }
    Sprite*         GetHpBarOut(){ return m_HpbarOut; }
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
    void            SetMyHpBar();
    void            SetEnemyHpBar();
    void            UpdateMyHpBar();
    void            UpdateOtherHpBar();
    void            Move();
    void            Crash();

    UnitType        GetUnitType(){ return m_UnitType; }

protected:
    MoveState*      m_MoveState	= nullptr;
    MoveState*      m_StandbyState = nullptr;
    MoveState*      m_MovingState = nullptr;
    MoveState*      m_CrashedState = nullptr;

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
    Sprite*         m_RealSprite = nullptr;
    Sprite*         m_Sprite = nullptr; // 투명 스프라이트
    Sprite*         m_MyHpBar = nullptr;
    Sprite*         m_EnemyHpBar = nullptr;
    Sprite*         m_HpbarOut = nullptr;
    UnitType        m_UnitType;

    friend class ObjectManager;
};