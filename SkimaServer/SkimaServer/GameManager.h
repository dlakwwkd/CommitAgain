#pragma once
#include <map>
#include "RefCountable.h"

class Game;
class GameRoom;
class b2World;

class GameManager : public RefCountable
{
public:
	GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
	virtual ~GameManager(){ DeletePhyWorld(); }
	
	GameRoom*	CreateRoom();
	void		DeleteRoom(int roomId);

	GameRoom*	SearchRoom(int roomId);
	int			SearchEmptyRoom();
	void		JoinRoom(int playerId, int roomId);
	void		OutRoom(int playerId, int roomId);

	void		CreateGame(int roomId);
	void		DeleteGame(int gameId);

	void		PlayerOut(int playerId);

	void		InitPhyWorld();
	void		DeletePhyWorld();
	
	void		Tick(float dt);
	void		LowTick();

private:
	typedef std::map<int, Game*> GameList;
	typedef std::map<int, GameRoom*> RoomList;
	GameList	m_GameList;
	RoomList	m_RoomList;
	int			m_MakeRoomNum;

	b2World*	m_World;
};

extern GameManager* GGameManager;