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
	m_UnitID = -1;
	m_Hp = m_MaxHp = -1;
    m_Damage = 0;
    m_Speed = -1;
    m_Contacting = false;
    m_TargetPos = { -1, -1 };

    m_State = m_StandbyState = new StandbyState;
    m_MovingState = new MovingState;
    m_CrashedState = new CrashedState;
}

Unit::~Unit()
{
	delete m_StandbyState;
    delete m_MovingState;
    delete m_CrashedState;
	CallFuncAfter(1, GGameManager, &GameManager::DeleteBody, m_Body);
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
	circle.m_radius = REDUCE(scale);

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
	m_UnitID = SET_SIDE_TYPE(m_UnitID, type);
	m_Owner = owner;
	m_Owner->UnitListPush(m_UnitID, this);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(initPos.x, initPos.y);
	m_Body = GGameManager->GetWolrd()->CreateBody(&bodyDef);

	b2PolygonShape square;
	square.SetAsBox(REDUCE(scale.x), REDUCE(scale.y));

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
            EXTEND(curPos.x), EXTEND(curPos.y));
    }
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
		break;
	};

    auto curPos = m_Body->GetPosition();
    auto expectPos = curPos;

    if (isCrashing)
    {
        auto velocity = m_Body->GetLinearVelocity();
        velocity *= 1.0f / DAMPING;
        expectPos += velocity;
        printf(" - Crashing:    UnitID: %d,  \t   expectPos:   x : %.f \t y : %.f\n", INIT_TYPE(m_UnitID),
            EXTEND(expectPos.x), EXTEND(expectPos.y));
    } 
    else
    {
        EndCrash();
    }

    client->CrashedBroadCast(m_UnitID, curPos, expectPos, isCrashing);
}

void Unit::Damaged(int damage)
{
    m_Hp -= damage;
    m_Owner->GetClient()->HpBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Hp);

    switch (GET_MAIN_TYPE(m_UnitID))
    {
    case UNIT_HERO:
        if (m_Hp <= 0)
        {
            CallFuncAfter(MANAGER_UPDATE_INTERVAL, GGameManager, &GameManager::GameOver, m_Owner);
        }
        break;
    case UNIT_OBSTRUCT:
        if (m_Hp <= 0)
        {
            auto gameId = m_Owner->GetRoomID();

            auto game = GGameManager->SearchGame(gameId);
            if (game == nullptr)
            {
                printf("Object Game Can't Find");
            }
            auto map = game->GetMap();
            CallFuncAfter(MANAGER_UPDATE_INTERVAL, map, &Map::ObjectBreak, m_UnitID);
        }
        break;
    default:
        break;
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
