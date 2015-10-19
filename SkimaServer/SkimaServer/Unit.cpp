#include "stdafx.h"
#include "Unit.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Player.h"
#include "ClientSession.h"
#include "Game.h"
#include "Map.h"
#include "BuffSkill.h"
#include "Item.h"
#include "Missile.h"


Unit::Unit()
{
    m_State = m_StandbyState = new StandbyState();
    m_MovingState = new MovingState();
    m_CrashedState = new CrashedState();
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
    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        printf(" - TryMove Failed ! : client is invalid \n");
        return;
    }
    auto displacement = m_TargetPos - m_Body->GetPosition();
    if (displacement.Normalize() < 0.5f)
    {
        m_Body->SetAwake(false);
        return;
    }
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    client->TryMoveBroadCast(m_UnitID, m_TargetPos);
}

void Unit::ReachCheck()
{
    auto curPos = m_Body->GetPosition();
    auto distance = m_TargetPos - curPos;
    if (distance.Length() < 0.5f)
    {
        EndMove();
    }
}

void Unit::Crashing()
{
    m_IsHidden = false;
    CurPosSync();
}

void Unit::CurPosSync()
{
    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        printf(" - CurPosSync Failed ! : client is invalid \n");
        return;
    }
    auto curPos = m_Body->GetPosition();
    client->SyncPosBroadCast(m_UnitID, curPos);
}


void Unit::Damaged(int damage)
{
    if (m_IsDead)
    {
        return;
    }
    if (GET_MAIN_TYPE(m_UnitID) == UNIT_ITEM)
    {
        return;
    }

    if (m_Buff && m_Buff->IsShieldOn())
    {
        m_Shield -= damage;

        if (m_Shield <= 0)
        {
            damage = m_Shield;
            m_Shield = 0;
            m_Buff->ShieldDestroy();
        }
        else
        {
            damage = 0;
        }
    }
    m_Hp -= damage;

    if (m_Hp <= 0)
    {
        m_IsDead = true;
        CallFuncAfter(1, GGameManager, &GameManager::DeadUnit, this, m_Owner->GetRoomID());
        //printf(" - CallFuncAfter: DeadUnit : MainType: %d, SideType: %d, UnitID: %d\n", GET_MAIN_TYPE(m_UnitID), GET_SIDE_TYPE(m_UnitID), INIT_TYPE(m_UnitID));
    }
    m_Owner->GetClient()->HpBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Hp);
}

void Unit::UseBuff(BuffTarget type)
{
    switch (type)
    {
    case BUFF_SPEED:
        m_Buff->SpeedBuff();
        break;
    case BUFF_SHIELD:
        m_Buff->ShieldBuff();
        break;
    case BUFF_HP:
        m_Buff->HpBuff();
        break;
    case BUFF_DAMAGE:
        m_Buff->DamageBuff();
        break;
    case BUFF_COOLTIME:
        m_Buff->CooltimeBuff();
        break;
    }
}



void Unit::TryMove(const b2Vec2& targetPos)
{
    m_TargetPos = targetPos;
    m_State->TryMove(this);
}

void Unit::Crashed(Unit* contactUnit)
{
    if (m_IsDead)
    {
        return;
    }
    switch (GET_MAIN_TYPE(m_UnitID))
    {
    case UNIT_MISSILE:
        dynamic_cast<Missile*>(this)->MissileExplosion();
        return;
    }
    auto client = m_Owner->GetClient();
    if (client == nullptr)
    {
        printf(" - Crashed Failed ! : client is invalid \n");
        return;
    }
    auto curPos = m_Body->GetPosition();
    auto expectPos = curPos;
    auto velocity = m_Body->GetLinearVelocity();
    velocity *= 1.0f / DAMPING;
    expectPos += velocity;

    m_State->Crashed(this);
	if (client->GetPlayer())
		client->CrashedBroadCast(m_UnitID, curPos, expectPos);
}
