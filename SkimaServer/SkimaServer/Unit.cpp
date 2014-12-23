#include "stdafx.h"
#include "Unit.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Player.h"
#include "ClientSession.h"
#include "Game.h"
#include "Map.h"

Unit::Unit()
{
    m_State = m_StandbyState = new StandbyState;
    m_MovingState = new MovingState;
    m_CrashedState = new CrashedState;
}

Unit::~Unit()
{
    GGameManager->DeleteBody(m_Body);
    delete m_StandbyState;
    delete m_MovingState;
    delete m_CrashedState;
}

void Unit::SetDynamicBody(Player* owner, int type, const b2Vec2& initPos, float scale)
{
    m_UnitID = SET_SIDE_TYPE(m_UnitID, type);
    m_Owner = owner;
    m_Owner->UnitListPush(m_UnitID, this);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(initPos.x, initPos.y);
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = Reduce(scale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}

void Unit::SetStaticBody(Player* owner, int type, const b2Vec2& initPos, const b2Vec2& scale)
{
    if (owner == nullptr)
    {
        return;
    }

    m_UnitID = SET_SIDE_TYPE(m_UnitID, type);
    m_Owner = owner;
    m_Owner->UnitListPush(m_UnitID, this);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(initPos.x, initPos.y);
    m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

    b2PolygonShape square;
    square.SetAsBox(Reduce(scale.x), Reduce(scale.y));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &square;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    m_Body->CreateFixture(&fixtureDef);
    m_Body->SetUserData(this);
}


void Unit::Moving()
{
    auto curPos = m_Body->GetPosition();
    auto distance = m_TargetPos - curPos;
    if (distance.Length() < 0.5f)
    {
        EndMove();
        printf(" - Reach: UnitID:  %d, \t\t\t x : %.f \t y : %.f\n", INIT_TYPE(m_UnitID),
            Extend(curPos.x), Extend(curPos.y));
    }
}

void Unit::Chasing()
{
    if (m_State == m_CrashedState)
    {
        return;
    }
    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    game->Targeting(this);

    auto currentPos = m_Body->GetPosition();
    auto displacement = m_TargetPos - currentPos;
    displacement.Normalize();
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    m_Owner->GetClient()->TryMoveBroadCast(m_UnitID, currentPos, m_TargetPos);
    m_State->TryMove(this);
}

void Unit::Crashing(bool isCrashing)
{
    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        EndCrash();
        printf(" - Crashing Failed ! : client is invalid \n");
        return;
    }
    switch (GET_MAIN_TYPE(m_UnitID))
    {
    case UNIT_MISSILE:
        isCrashing = false;
        CallFuncAfter(1, GGameManager, &GameManager::DeadUnit, this);
        break;
    };

    auto curPos = m_Body->GetPosition();
    auto expectPos = curPos;
    
    if (isCrashing)
    {
        m_IsHidden = false;
        auto velocity = m_Body->GetLinearVelocity();
        velocity *= 1.0f / DAMPING;
        expectPos += velocity;
        printf(" - Crashing:    UnitID: %d,  \t   expectPos:   x : %.f \t y : %.f\n", INIT_TYPE(m_UnitID),
            Extend(expectPos.x), Extend(expectPos.y));
    } 
    else
    {
        EndCrash();
    }

    client->CrashedBroadCast(m_Owner->GetPlayerID(), m_UnitID, curPos, expectPos, isCrashing);
}

void Unit::Damaged(int damage)
{
    m_Hp -= damage;
    m_Owner->GetClient()->HpBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Hp);

    if (m_Hp <= 0)
    {
        CallFuncAfter(1, GGameManager, &GameManager::DeadUnit, this);
    }
}


void Unit::TryMove(const b2Vec2& currentPos, const b2Vec2& targetPos)
{
    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        printf(" - TryMove Failed ! : client is invalid \n");
        return;
    }

    auto displacement = targetPos - m_Body->GetPosition();
    if (displacement.Normalize() < 0.5f)
    {
        m_Body->SetLinearVelocity(b2Vec2(0, 0));
        return;
    }
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    m_TargetPos = targetPos;
    m_State->TryMove(this);

    client->TryMoveBroadCast(m_UnitID, currentPos, m_TargetPos);
}
