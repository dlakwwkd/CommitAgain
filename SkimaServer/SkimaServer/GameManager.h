#pragma once
#include "RefCountable.h"
class Game;
class GameRoom;
class Player;
class b2World;
class ContactListener;
class Unit;

typedef std::map<int, Game*> GameList;
typedef std::map<int, GameRoom*> RoomList;

struct Rect ///< 간단한 구조체라도 디폴트 초기화 및 멤버변수 이름 코딩 컨벤션 맞추는 습관을..
{
    float top;
    float bottom;
    float left;
    float right;
};

#define MAX_PLAYER_NUM 2

class GameManager : public RefCountable
{
public:
    GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
    virtual ~GameManager(){ DeletePhyWorld(); } 

    void                Tick(float dt);
    void                LowTick();

    GameRoom*           CreateRoom();
    void                DeleteRoom(int roomId);
    GameRoom*           SearchRoom(int roomId);
    int                 SearchEmptyRoom();
    void                JoinRoom(int roomId, Player* player);

    Game*               SearchGame(int gameId);
    void                CreateGame(int gameId);
    void                DeleteGame(int gameId);
    void                GameOver(Player* player);

    void                PlayerOut(Player* player);

    bool                ApplyDamage(Unit* unitA, Unit* unitB);
    void                CrashDamage(Unit* unitA, Unit* unitB);
    void                FieldDamage(Player* caster, Rect* range, int damage);

public:
    b2World*            GetWolrd(){ return m_World; } ///< 내부 private 멤버를 외부에 포인터로 노출 시키는 것은 OOP에 어긋남.
	///#이런 경우는 m_WOrld가 여기 있을 곳이 아니던가.. 이 객체에서 Create/Destroy를 하던가..

    ContactListener*    GetContact(){ return m_Contact; }
    void                DeleteBody(b2Body* body){ m_World->DestroyBody(body); } ///< 어떤 곳에서는 요놈을 쓰고, 어떤 곳에서는 GetWorld로 가져온 다움에 요놈을 쓰고.. 뭔가 이상하지 않음?
private:
    void                InitPhyWorld();
    void                DeletePhyWorld();

private:
    GameList            m_GameList;
    RoomList            m_RoomList;
    int                 m_MakeRoomNum;

private:
    b2World*            m_World;
    ContactListener*    m_Contact;
};

extern GameManager* GGameManager;