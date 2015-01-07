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
#include "Mob.h"
#include "Item.h"

GameManager* GGameManager = nullptr;

///////////////////////////////////////////////////////////////////////////
/*
    메인 틱 : 물리 계산 및 각 게임의 틱 호출
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
    낮은 주기의 틱 : 정지해 있는 바디들의 현재 위치 동기화
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::LowTick()
{
    for (b2Body* b = m_World->GetBodyList(); b; b = b->GetNext())
    {
        if (!b->IsAwake())
        {
            if (b->GetUserData())
            {
                auto unit = static_cast<Unit*>(b->GetUserData());
                unit->CurPosSync();
            }
        }
    }
    //printf(" - Total Body Num : %d \n", m_World->GetBodyCount());
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
GameRoom* GameManager::CreateRoom(const RoomInfo& roomInfo)
{
    auto room = new GameRoom(roomInfo);
    m_RoomList.insert(RoomList::value_type(room->GetRoomID(), room));
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
    auto game = new Game(room->second);
    m_GameList.insert(GameList::value_type(gameId, game));
    game->InitGame(room->second->GetRoomInfo().mRoomType);
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
    player->SetGameOver();

    auto game = player->GetGame();
    if (game == nullptr)
    {
        printf(" - GameOver Failed ! : relevant game isn't \n");
        return;
    }
    auto room = m_RoomList.find(player->GetRoomID());
    if (room == m_RoomList.end())
    {
        printf(" - GameOver Failed ! : relevant room isn't \n");
        return;
    }

    auto winTeam = TEAM_N;
    if (false == game->DecideWinTeam(winTeam))
    {
        return;
    }
    if (game->IsStart())
    {
        game->EndGame();
        room->second->SetIsGameStart(false);
        player->GetClient()->GameOverCast(winTeam);
    }
    DeleteGame(game->GetGameID());
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

    auto game = player->GetGame();
    if (game != nullptr)
    {
        game->OutPlayer(playerId);
        GameOver(player);
        player->SetGame(nullptr);
    }
    auto room = m_RoomList.find(roomId);
    if (room != m_RoomList.end())
    {
        room->second->OutPlayer(playerId);
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
        unitA->Damaged(unitB->GetDamage() + unitB->GetDamageBonus());
        unitB->Damaged(unitA->GetDamage() + unitA->GetDamageBonus());
    }
}

void GameManager::FieldDamage(Player* caster, Rect* range, int damage)
{
    if (!caster || !range)
    {
        printf(" - FieldDamage() Faild ! : invalid player or range \n");
        return;
    }
    auto game = caster->GetGame();
    if (game == nullptr)
    {
        printf(" - FieldDamage() Faild ! : invalid game \n");
        return;
    }
    if (caster->GetTeam() != TEAM_C)
    {
        damage += caster->GetMyHero()->GetDamageBonus();
    }
    for (auto& player : game->m_PlayerList)
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

void GameManager::FieldCheck(Item* item)
{
    if (!item)
    {
        printf(" - FieldCheck() Faild ! : invalid item \n");
        return;
    }
    auto computer = item->GetOwner();
    auto game = computer->GetGame();
    if (game == nullptr)
    {
        printf(" - FieldCheck() Faild ! : invalid game \n");
        return;
    }
    auto range = item->GetTakeRange();

    for (auto& player : game->m_PlayerList)
    {
        if (player.second->GetTeam() == computer->GetTeam())
        {
            continue;
        }
        for (auto& unit : player.second->GetUnitList())
        {
            auto pos = unit.second->GetBody()->GetPosition();

            if (pos.x > range->m_Left && pos.x < range->m_Right &&
                pos.y > range->m_Bottom && pos.y < range->m_Top)
            {
                if (GET_MAIN_TYPE(unit.second->GetUnitID()) != UNIT_HERO)
                {
                    continue;
                }
                item->SetDead();
                CallFuncAfter(1, GGameManager, &GameManager::DeadUnit, item, computer->GetRoomID());
                unit.second->UseBuff(item->GetBuffTarget());
                return;
            }
        }
    }
}

void GameManager::DeadUnit(Unit* unit, int gameId)
{
    if (m_GameList.find(gameId) == m_GameList.end())
    {
        return;
    }
    auto unitId = unit->GetUnitID();
    auto owner = unit->GetOwner();
    //printf(" - Dead Unit : MainType: %d, SideType: %d, UnitID: %d\n", GET_MAIN_TYPE(unitId), GET_SIDE_TYPE(unitId), INIT_TYPE(unitId));

    switch(GET_MAIN_TYPE(unitId))
    {
    case UNIT_HERO:
        owner->UnitListPop(unit->GetUnitID());
        owner->DeadHero();
        GameOver(owner);
        return;
    }
    unit->Dead();
    owner->UnitListPop(unit->GetUnitID());
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
