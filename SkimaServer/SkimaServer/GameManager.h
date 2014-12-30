#pragma once
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
enum WallDirection
{
    NW,
    NE,
    SW,
    SE,
};


#define MAX_PLAYER_NUM 8

class GameManager : public RefCountable
{
public:
    GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
    virtual ~GameManager(){ DeletePhyWorld(); }

    void                Tick(float dt);
    void                LowTick();
    void                CollectGarbageGames();
    void                DestroyTimer(Timer* timer);

    GameRoom*           CreateRoom(RoomInfo roomInfo);
    void                DeleteRoom(int roomId);
    GameRoom*           SearchRoom(int roomId);
    int                 SearchEmptyRoom();
    const RoomList&     GetRoomList(){ return m_RoomList; }
    void                JoinRoom(int roomId, Player* player);

    Game*               SearchGame(int gameId);
    void                CreateGame(int gameId);
    void                DeleteGame(int gameId);
    void                GameOver(Player* player);

    void                PlayerOut(Player* player);

    void                CrashDamage(Unit* unitA, Unit* unitB);
    void                FieldDamage(Player* caster, Rect* range, int damage);
    void                FieldCheck(Item* item, b2Vec2 pos, float scale);
    void                WallFieldDamage(Player* caster, b2PolygonShape* wallShape, int damage);
	void                DeadUnit(Unit* unit);

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
    int                 m_MakeRoomNum;

private:
    b2World*            m_World = nullptr;
    ContactListener*    m_Contact = nullptr;
};

extern GameManager* GGameManager;