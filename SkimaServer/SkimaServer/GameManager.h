#pragma once
#include <map>
#include "RefCountable.h"

class Game;
class GameRoom;
class Player;
class b2World;
class ContactListener;

class GameManager : public RefCountable
{
public:
	GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
	virtual ~GameManager(){ DeletePhyWorld(); }
	
	GameRoom*			CreateRoom();
	void				DeleteRoom(int roomId);

	GameRoom*			SearchRoom(int roomId);
	int					SearchEmptyRoom();
	void				JoinRoom(int id, Player* player, int roomId);
	void				OutRoom(int playerId, int roomId);

	Game*				SearchGame(int playerId);
	void				CreateGame(int roomId);
	void				DeleteGame(int gameId);

	Player*				SearchPlayer(int playerId);
	void				PlayerOut(int playerId);

	//void				UnitMoveSet(b2Vec2 targetPos, b2Vec2 currentPos, int playerId);

	void				Tick(float dt);
	void				LowTick();

public:
	b2World*			GetWolrd(){ return m_World; }
	ContactListener*	GetContact(){ return m_Contact; }

	void				InitPhyWorld();
	void				DeletePhyWorld();

private:
	typedef std::map<int, Game*> GameList;
	typedef std::map<int, GameRoom*> RoomList;
	GameList			m_GameList;
	RoomList			m_RoomList;
	int					m_MakeRoomNum;

private:
	b2World*			m_World;
	ContactListener*	m_Contact;
};

extern GameManager* GGameManager;