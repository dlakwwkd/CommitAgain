﻿#pragma once
#include "RefCountable.h"
#include "../../PacketType.h"
class Game;
class GameRoom;
class Player;
class b2World;
class ContactListener;
class Unit;
class Timer;
class Item;

typedef std::map<int, Game*>        GameList;
typedef std::map<int, GameRoom*>    RoomList;

struct Rect
{
    float m_Top		= 0;
    float m_Bottom	= 0;
    float m_Left	= 0;
    float m_Right	= 0;
};

#define MAX_PLAYER_NUM 8

class GameManager : public RefCountable
{
public:
    GameManager(){ InitPhyWorld(); }
    virtual ~GameManager(){ DeletePhyWorld(); }

    void                Tick(float dt);
    void                LowTick();
    void                DestroyTimer(Timer* timer);

    const RoomList&     GetRoomList(){ return m_RoomList; }
    GameRoom*           CreateRoom(const RoomInfo& roomInfo);
    void                DeleteRoom(int roomId);
    GameRoom*           SearchRoom(int roomId);
    int                 SearchEmptyRoom();

    Game*               SearchGame(int gameId);
    void                CreateGame(int gameId);
    void                DeleteGame(int gameId);
    void                GameOver(Player* player);

    void                PlayerOut(Player* player);

    void                CrashDamage(Unit* unitA, Unit* unitB);
    void                FieldDamage(Player* caster, Rect* range, int damage);
    void                FieldCheck(Item* item);
    void                DeadUnit(Unit* unit, int gameId);

public:
    b2World*            GetWolrd(){ return m_World; }
    ContactListener*    GetContact(){ return m_Contact; }
	void                DeleteBody(b2Body* body){ m_World->DestroyBody(body); }
private:
    void                InitPhyWorld();
    void                DeletePhyWorld();

private:
    GameList            m_GameList;
    RoomList            m_RoomList;

private:
    b2World*            m_World = nullptr;
    ContactListener*    m_Contact = nullptr;
};

extern GameManager* GGameManager;