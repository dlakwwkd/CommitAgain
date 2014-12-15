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
            if (unit)
            {
                //현재 위치 동기화 (패킷을 날려주기 위해)
                unit->Crashing(false);
            }
        }
    }
    CallFuncAfter(MANAGER_UPDATE_INTERVAL * 3, this, &GameManager::LowTick);
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
    m_RoomList[roomId]->JoinPlayer(player);
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
        DeleteGame(gameId);
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
    game->second->EndGame();
    player->GetClient()->GameOverCast(player->GetPlayerID());
    DeleteGame(game->second->GetGameID());
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
        if (game->second->GetPlayerListSize() < 2)
        {
            game->second->EndGame();
            player->GetClient()->GameOverCast(playerId);
            DeleteGame(roomId);
        }
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
bool GameManager::ApplyDamage(Unit* unitA, Unit* unitB)
{
    if (!unitA || !unitB || (unitA->GetOwner()->GetTeam() == unitB->GetOwner()->GetTeam()))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GameManager::CrashDamage(Unit* unitA, Unit* unitB)
{
    unitA->Damaged(unitB->GetUnitDamage());
    unitB->Damaged(unitA->GetUnitDamage());
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

            if (pos.x > range->left && pos.x < range->right &&
                pos.y > range->bottom && pos.y < range->top)
            {
                unit.second->Damaged(damage);
            }
        }
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
