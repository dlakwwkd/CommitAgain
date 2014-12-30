#pragma once
#include "Enums.h"
#include "PacketType.h"
#include "FSM.h"

USING_NS_CC;

class Skill;

typedef std::map<Direction, Animation*> MoveMotion;

class Unit
{
public:
    Unit();
    virtual ~Unit();

    void            SetType(int type){ m_UnitID = SET_SIDE_TYPE(m_UnitID, type); }
    void            SetPlayerID(int playerID){ m_PlayerID = playerID; }
    void            SetUnitID(int unitID){ m_UnitID = unitID; }
    void            SetSpeed(float speed) { m_Speed = speed; }
    void            SetCooltimeBonus(int bonus){ m_CooltimeBonus = bonus; }
    void            SetTargetPos(Vec2 pos){ m_TargetPos = pos; }
    void            SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
    void            SetUnitHiddenState(bool isHidden) { m_IsHidden = isHidden; }

    UnitType        GetUnitType(){ return m_UnitType; }
    Vec2            GetTargetPos(){ return m_TargetPos; }
    int             GetPlayerID(){ return m_PlayerID; }
    int             GetUnitID(){ return m_UnitID; }
    int             GetCooltimeBonus(){ return m_CooltimeBonus; }
    float           GetMaxHp(){ return m_MaxHp; }
    float           GetCurHp(){ return m_CurHp; }
    float           GetSpeed(){ return m_Speed; }
    bool            GetHeroHiddenState(){ return m_IsHidden; }

    Sprite*         GetCenterSprite(){ return m_CenterSprite; }
    Sprite*         GetRealSprite(){ return m_RealSprite; }
    Sprite*         GetHpBarFrame(){ return m_HpBarFrame; }
    Sprite*         GetHpBar(){ return m_HpBar; }

    MoveState*      GetMoveState(){ return m_MoveState; }
    MoveState*      GetStandbyState(){ return (MoveState*)m_StandbyState; }
    MoveState*      GetMovingState(){ return (MoveState*)m_MovingState; }
    MoveState*      GetCrashedState(){ return (MoveState*)m_CrashedState; }

    void            TryMove(){ m_MoveState->TryMove(this); }
    void            EndMove(){ m_MoveState->EndMove(this); }
    void            Crashed(){ m_MoveState->Crashed(this); }
    void            EndCrash(){ m_MoveState->EndCrash(this); }
    void            Movement(){ m_MoveState->Movement(this); }

    void            Move();
    void            Crash();

    void            InitCenterSprite();
    void            InitRealSprite();
    void            SetAllSpriteVisible();
    void            SetHp(int curHp);
    void            SetMyHpBar();
    void            SetEnemyHpBar();
    void            SetUnitHpBar();
    void            UpdateHpBar();
protected:
    void            SetHeroHpBar(const char* barImage);
    void            Damaged();

protected:
    UnitType        m_UnitType;
    std::string     m_Name;
    int             m_PlayerID;
    int             m_UnitID;
    int             m_CooltimeBonus;
    float           m_MaxHp;
    float           m_CurHp;
    float           m_Speed;
    bool            m_InUse;
    bool            m_IsHidden;
    Vec2            m_TargetPos;

protected:
    MoveMotion      m_MoveMotionByDir;
    Sprite*         m_CenterSprite = nullptr; // 투명 스프라이트
    Sprite*         m_RealSprite = nullptr;
    Sprite*         m_HpBarFrame = nullptr;
    Sprite*         m_HpBar = nullptr;
    Sprite*         m_Damaged = nullptr;

protected:
    MoveState*      m_MoveState = nullptr;
    MoveState*      m_StandbyState = nullptr;
    MoveState*      m_MovingState = nullptr;
    MoveState*      m_CrashedState = nullptr;

    friend class ObjectManager;
};