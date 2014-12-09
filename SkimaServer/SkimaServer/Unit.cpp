#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "ClientSession.h"

Unit::Unit()
{
    static int makeId = 0;
    m_UnitID = ++makeId;

    m_Owner = nullptr;
    m_Hp = m_MaxHp = -1;
    m_Damage = 0;
    m_Speed = -1;
    m_Contacting = false;
    m_TargetPos = { -1, -1 };
    m_Body = nullptr;

    m_State = m_StandbyState = new StandbyState;
    m_MovingState = new MovingState;
    m_CrashedState = new CrashedState;
}

Unit::~Unit()
{
    delete m_StandbyState;
    delete m_MovingState;
    delete m_CrashedState;
}


void Unit::Moving()
{
    auto curPos = m_Body->GetPosition();
    auto distance = m_TargetPos - curPos;
    if (distance.Length() < 0.5f)
    {
        EndMove();
        printf(" - Reach: UnitID:  %d, \t\t\t\t X : %.f\tY : %.f\n", m_UnitID,
            EXTEND(curPos.x), EXTEND(curPos.y));
    }
}

void Unit::Crashing(bool isCrashing)
{
    switch (GET_MAIN_TYPE(m_UnitID))
    {
    case UNIT_HERO:
        if (m_Hp <= 0) IamDead();
        break;
    case UNIT_MISSILE:
        isCrashing = false;
        Extinction();
        break;
    };

    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        EndCrash();
        printf(" - Crashing Failed ! : client is invalid \n");
        return;
    }

    auto curPos = m_Body->GetPosition();
    auto expectPos = curPos;

    if (isCrashing)
    {
        auto velocity = m_Body->GetLinearVelocity();
        velocity *= 1.0f / DAMPING;
        expectPos += velocity;
        printf(" - Crashing: UnitID:  %d, \t\t\t expectPos: X : %.f\tY : %.f\n", m_UnitID,
            EXTEND(expectPos.x), EXTEND(expectPos.y));
    } 
    else
    {
        EndCrash();
    }

    client->CrashedBroadCast(m_UnitID, curPos, expectPos, isCrashing);
}


void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
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

    client->SendHeroInfo(m_UnitID, currentPos, m_TargetPos);
}

void Unit::IamDead()
{

}
