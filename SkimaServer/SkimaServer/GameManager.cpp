#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "ContactListener.h"
#include "Scheduler.h"
#include "Config.h"


GameManager* GGameManager = nullptr;


///////////////////////////////////////////////////////////////////////////
/*
    GameRoom 관련
*/
///////////////////////////////////////////////////////////////////////////
GameRoom* GameManager::CreateRoom()
{
    if (m_MakeRoomNum == 0)
        LowTick();

    if (m_RoomList.find(m_MakeRoomNum) != m_RoomList.end())
    {
        DeleteRoom(m_MakeRoomNum);
    }
    GameRoom* room = new GameRoom(++m_MakeRoomNum);
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

void GameManager::OutPlayer(int roomId, int playerId)
{
    if (roomId < 0 || playerId < 0)
    {
        printf(" - OutPlayer Failed ! : invalid ID \n");
        return;
    }
    auto game = m_GameList.find(roomId);
    if (game != m_GameList.end())
    {
        game->second->OutPlayer(playerId);
        if (game->second->GetPlayerList().size() == 0)
        {
            DeleteGame(roomId);
        }
    }
    auto room = m_RoomList.find(roomId);
    if (room != m_RoomList.end())
    {
        room->second->OutPlayer(playerId);
        if (room->second->GetPlayerList().size() == 0)
        {
            DeleteRoom(roomId);
        }
    }
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
    DeleteRoom(gameId);
    m_GameList[gameId] = game;
    game->InitGame();
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



///////////////////////////////////////////////////////////////////////////
/*
    Player 관련
*/
///////////////////////////////////////////////////////////////////////////
Player* GameManager::SearchPlayer(int playerId)
{
    if (playerId < 0)
    {
        printf(" - SearchPlayer Failed ! : playerId is invalid \n");
        return nullptr;
    }
    for (auto& game : m_GameList)
    {
        for (auto& player : game.second->GetPlayerList())
        {
            if (player.first == playerId)
            {
                return player.second;
            }
        }
    }
    printf(" - SearchPlayer Failed ! : relevant player isn't \n");
    return nullptr;
}

void GameManager::PlayerOut(int playerId)
{
    if (playerId < 0)
    {
        printf(" - PlayerOut Failed ! : playerId is invalid \n");
        return;
    }
    auto player = SearchPlayer(playerId);
    if (player == nullptr)
    {
        printf(" - PlayerOut Failed ! : relevant player isn't \n");
        return;
    }
    OutPlayer(player->GetRoomID(), playerId);
}




///////////////////////////////////////////////////////////////////////////
/*
    매 프레임마다 실행	
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::Tick(float dt)
{
    m_World->Step(dt, 8, 3);

    for (auto& room : m_RoomList)
    {
        if (room.second->IsAllReady())
        {
            // 게임 구동 시작!;
            printf(" - All Player is Ready ! :: %d Room is Game Start !! \n", room.first);
            CallFuncAfter(MANAGER_UPDATE_INTERVAL, this, &GameManager::CreateGame, room.first);
            room.second->InitReady();
        }
    }

	/// 매 프레임마다 모든 게임 리스트와 그 플레이어를 순회하는 것은 좋은 선택이 아님! 사실 게임 시작 전까지의 모든 과정은 프레임 처리 없이 되는거다..
    for (auto& game : m_GameList)
    {
        for (auto& player : game.second->GetPlayerList())
        {
            auto client = GClientManager->GetClient(player.first);
            if (client == nullptr)
            {
                PlayerOut(player.first);
                continue;
            }

            if (client->GetPlayer()->GetMyHero()->GetUnitHp() <= 0)
            {

            }

            if (game.second->IsReady())
            {
                CallFuncAfter(MANAGER_UPDATE_INTERVAL, client, &ClientSession::ServerRunComplete);
                game.second->SetIsReady(false);
            }

            if (!game.second->IsStart() && game.second->GetLoadedPlayerNum() >= 2)
            {
                client->StartGame();
                game.second->SetIsStart(true);
            }

            if (!game.second->IsStart())
                continue;

            for (auto& unit : player.second->GetUnitList())
            {
                unit.second->Movement();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
/*
    낮은 주기로 반복 실행
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
            unit->Crashing(false);
            ++j;
        }
        ++i;
    }
    printf(" - Total Sleeping Body Num [%2d/%2d] \n", j, i);
    CallFuncAfter(MANAGER_UPDATE_INTERVAL*3, this, &GameManager::LowTick);
}



///////////////////////////////////////////////////////////////////////////
/*
    데미지 계산 함수들
*/
///////////////////////////////////////////////////////////////////////////
bool GameManager::ApplyDamage(Unit* unitA, Unit* unitB)
{
    if (unitA->GetPlayerID() == unitB->GetPlayerID())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GameManager::ExchangeDamage(Unit* unitA, Unit* unitB)
{
    int damageA = unitA->GetUnitDamage();
    int damageB = unitB->GetUnitDamage();
    int unitAHp = unitA->GetUnitHp() - damageB;
    int unitBHp = unitB->GetUnitHp() - damageA;

    unitA->SetUnitHp(unitAHp);
    unitB->SetUnitHp(unitBHp);

    int AplayerId = unitA->GetPlayerID();
    int BplayerId = unitB->GetPlayerID();

    GClientManager->GetClient(AplayerId)->HpBroadCast(AplayerId, unitA->GetUnitID(), unitAHp);
    GClientManager->GetClient(BplayerId)->HpBroadCast(BplayerId, unitB->GetUnitID(), unitBHp);
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
