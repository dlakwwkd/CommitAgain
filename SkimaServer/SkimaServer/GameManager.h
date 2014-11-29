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

#define PTM_RATIO 32

#define EXTEND(f) (f)*PTM_RATIO
#define REDUCE(f) (f)/PTM_RATIO

#define INCREASE(v) {EXTEND((v).x), EXTEND((v).y)}
#define DECREASE(v) {REDUCE((v).x), REDUCE((v).y)}

#define CONVERT_IN(v, roomID) {REDUCE((v).x), REDUCE((v).y + (roomID)*MAX_MAP_SIZE_Y)}
#define CONVERT_OUT(v, roomID) {EXTEND((v).x), EXTEND((v).y) - (roomID)*MAX_MAP_SIZE_Y}

class GameManager : public RefCountable
{
public:
	GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
	virtual ~GameManager(){ DeletePhyWorld(); }
	
	GameRoom*			CreateRoom();
	void				DeleteRoom(int roomId);

	GameRoom*			SearchRoom(int roomId);
	int					SearchEmptyRoom();
	void				JoinRoom(int roomId, Player* player);
	void				OutPlayer(int roomId, int playerId);

	Game*				SearchGame(int gameId);
	void				CreateGame(int gameId);
	void				DeleteGame(int gameId);

	Player*				SearchPlayer(int playerId);
	void				PlayerOut(int playerId);

	void				Tick(float dt);
	void				LowTick();

	bool				ApplyDamage(Unit* unitA, Unit* unitB);
	void				ExchangeDamage(Unit* unitA, Unit* unitB);

public:
	b2World*			GetWolrd(){ return m_World; }
	ContactListener*	GetContact(){ return m_Contact; }

private:
	void				InitPhyWorld();
	void				DeletePhyWorld();

private:
	GameList			m_GameList;
	RoomList			m_RoomList;
	int					m_MakeRoomNum;

private:
	b2World*			m_World;
	ContactListener*	m_Contact;
};

extern GameManager* GGameManager;