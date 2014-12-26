#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"
#include "Game.h"
#include "ContactListener.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Scheduler.h"
#include "Config.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"

GameManager* GGameManager = nullptr;

///////////////////////////////////////////////////////////////////////////
/*
    메인 틱
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::Tick(float dt)
{
    m_World->Step(dt, 8, 3);

    for (auto& game : m_GameList)
    {
        if (game.second->IsStart())
        {
            game.second->Tick(dt);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
/*
    낮은 주기의 틱
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::LowTick()
{
    int i = 0, j = 0;
    for (b2Body* b = m_World->GetBodyList(); b; b = b->GetNext())
    {
        if (!b->IsAwake())
        {
            auto unit = static_cast<Unit*>(b->GetUserData());
            if (!unit || unit->GetUnitID() < 0)
            {
				continue;
            }
            unit->CurPosSync();
        }
    }
    CallFuncAfter(MANAGER_UPDATE_INTERVAL, this, &GameManager::LowTick);
}

///////////////////////////////////////////////////////////////////////////
/*
    타이머 제거
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::DestroyTimer(Timer* timer)
{
    auto game = m_GameList.find(timer->GetGameId());
    if (game != m_GameList.end())
    {
        game->second->PopTimer(timer->GetTimerId());
    }
    delete timer;
}


///////////////////////////////////////////////////////////////////////////
/*
    GameRoom 관련
*/
///////////////////////////////////////////////////////////////////////////
GameRoom* GameManager::CreateRoom()
{
    if (++m_MakeRoomNum == 1)
    {
        LowTick();
    }
    if (m_RoomList.find(m_MakeRoomNum) != m_RoomList.end())
    {
        DeleteRoom(m_MakeRoomNum);
    }
    GameRoom* room = new GameRoom(m_MakeRoomNum);
    m_RoomList[m_MakeRoomNum] = room;
    return room;
}

void GameManager::DeleteRoom(int roomId)
{
    if (roomId < 0)
    {
        printf(" - DeleteRoom Failed ! : roomId is invalid \n");
        return;
    }
    auto room = m_RoomList.find(roomId);
    if (room == m_RoomList.end())
    {
        printf(" - DeleteRoom Failed ! : relevant room isn't \n");
        return;
    }
    delete room->second;
    m_RoomList.erase(room);
    printf(" - Destroy %d Room ! \n", roomId);
}

GameRoom* GameManager::SearchRoom(int roomId)
{
    if (roomId < 0)
    {
        printf(" - SearchRoom Failed ! : roomId is invalid \n");
        return nullptr;
    }
    auto room = m_RoomList.find(roomId);
    if (room == m_RoomList.end())
    {
        printf(" - SearchRoom Failed ! : relevant room isn't \n");
        return nullptr;
    }
    return room->second;
}

int GameManager::SearchEmptyRoom()
{
    for (auto& room : m_RoomList)
    {
        if (room.second->IsJoinAble())
        {
            return room.second->GetRoomID();
        }
    }
    printf(" - No Room ! \n");
    return -1;
}

void GameManager::JoinRoom(int roomId, Player* player)
{
    if (roomId < 0 || player == nullptr)
    {
        printf(" - JoinRoom Failed ! : invalid info \n");
        return;
    }
	auto room = m_RoomList.find(roomId);
	if (room == m_RoomList.end())
	{
		printf(" - JoinRoom Failed ! : relevant room isn't \n");
		return;
	}
	room->second->JoinPlayer(player);
}


///////////////////////////////////////////////////////////////////////////
/*
    Game 관련
*/
///////////////////////////////////////////////////////////////////////////
Game* GameManager::SearchGame(int gameId)
{
    if (gameId < 0)
    {
        printf(" - SearchGame Failed ! : gameId is invalid \n");
        return nullptr;
    }
    auto game = m_GameList.find(gameId);
    if (game == m_GameList.end())
    {
        printf(" - SearchGame Failed ! : relevant game isn't \n");
        return nullptr;
    }
    return game->second;
}

void GameManager::CreateGame(int gameId)
{
    if (gameId < 0)
    {
        printf(" - CreateGame Failed ! : gameId is invalid \n");
        return;
    }
    auto room = m_RoomList.find(gameId);
    if (room == m_RoomList.end())
    {
        printf(" - CreateGame Failed ! : room info is invalid \n");
        return;
    }
    if (m_GameList.find(gameId) != m_GameList.end())
    {
        printf(" - CreateGame Failed ! : gameId is duplicated \n");
        return;
    }
    Game* game = new Game(room->second);
    m_GameList[gameId] = game;
    game->InitGame();
    room->second->InitReady();
}

void GameManager::DeleteGame(int gameId)
{
    if (gameId < 0)
    {
        printf(" - DeleteGame Failed ! : gameId is invalid \n");
        return;
    }
    auto game = m_GameList.find(gameId);
    if (game == m_GameList.end())
    {
        printf(" - DeleteGame Failed ! : relevant game isn't \n");
        return;
    }
    delete game->second;
    m_GameList.erase(game);
    printf(" - Destroy %d Game ! \n", gameId);
}

void GameManager::GameOver(Player* player)
{
    if (player == nullptr)
    {
        return;
    }
    auto game = m_GameList.find(player->GetRoomID());
    if (game == m_GameList.end())
    {
        printf(" - GameOver Failed ! : relevant game isn't \n");
        return;
    }
    if (game->second->IsStart())
    {
        game->second->EndGame();
        player->GetClient()->GameOverCast(player->GetPlayerID());
    }
    DeleteGame(game->first);
}


///////////////////////////////////////////////////////////////////////////
/*
    Player 관련
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::PlayerOut(Player* player)
{
    if (player == nullptr)
    {
        printf(" - PlayerOut Failed ! : relevant player isn't \n");
        return;
    }
    auto playerId = player->GetPlayerID();
    auto roomId = player->GetRoomID();

    auto game = m_GameList.find(roomId);
    if (game != m_GameList.end())
    {
        game->second->OutPlayer(playerId);
        GameOver(player);
    }
    auto room = m_RoomList.find(roomId);
    if (room != m_RoomList.end())
    {
        room->second->OutPlayer(playerId);
        if (room->second->GetPlayerListSize() == 0)
        {
            DeleteRoom(roomId);
        }
    }
}


///////////////////////////////////////////////////////////////////////////
/*
    데미지 계산 함수들
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::CrashDamage(Unit* unitA, Unit* unitB)
{
    if (unitA->GetOwner()->GetTeam() != unitB->GetOwner()->GetTeam())
    {
        unitA->Damaged(unitB->GetDamage());
        unitB->Damaged(unitA->GetDamage());
    }
}

void GameManager::FieldDamage(Player* caster, Rect* range, int damage)
{
    if (!caster || !range)
    {
        printf(" - FieldDamage() Faild ! : invalid player or range \n");
        return;
    }
    auto game = m_GameList.find(caster->GetRoomID());
    if (game == m_GameList.end())
    {
        printf(" - FieldDamage() Faild ! : invalid gameID \n");
        return;
    }
    for (auto& player : game->second->m_PlayerList)
    {
        if (player.second->GetTeam() == caster->GetTeam())
        {
            continue;
        }
        for (auto& unit : player.second->GetUnitList())
        {
			auto pos = unit.second->GetBody()->GetPosition();

            if (pos.x > range->m_Left && pos.x < range->m_Right &&
                pos.y > range->m_Bottom && pos.y < range->m_Top)
            {
                unit.second->Damaged(damage);
            }
        }
    }
}

void GameManager::DeadUnit(Unit* unit)
{
    auto unitId = unit->GetUnitID();
    auto owner = unit->GetOwner();
    owner->UnitListPop(unit->GetUnitID());

    if (GET_MAIN_TYPE(unitId) == UNIT_HERO)
    {
        owner->DeadHero();
        GameOver(owner);
    }
}




///////////////////////////////////////////////////////////////////////////
/*
    물리세계 구축
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::InitPhyWorld()
{
    b2Vec2 gravity(0.0f, 0.0f);
    m_World = new b2World(gravity);

    m_World->SetAllowSleeping(true);
    m_World->SetContinuousPhysics(true);

    m_Contact = new ContactListener();
    m_World->SetContactListener((b2ContactListener*)m_Contact);
}

void GameManager::DeletePhyWorld()
{
    delete m_World;
    delete m_Contact;
}
