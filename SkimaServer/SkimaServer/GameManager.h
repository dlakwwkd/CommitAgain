#pragma once
#include <map>
#include "RefCountable.h"

class Game;
class GameRoom;
class b2World;
class ContactListener;
class Player;

class GameManager : public RefCountable
{
public:
	GameManager() : m_MakeRoomNum(0){ InitPhyWorld(); }
	virtual ~GameManager(){ DeletePhyWorld(); }
	
	GameRoom*			CreateRoom();
	void				DeleteRoom(int roomId);

	GameRoom*			SearchRoom(int roomId);
	int					SearchEmptyRoom();
	void				JoinRoom(int playerId, int roomId);
	void				OutRoom(int playerId, int roomId);

	Game*				SearchGame(int playerId);
	void				CreateGame(int roomId);
	void				DeleteGame(int gameId);

	Player*				SearchPlayer(int playerId);
	void				PlayerOut(int playerId);

	void				UnitMoveSet(b2Vec2 targetPos, b2Vec2 currentPos, int playerId);

	void				InitPhyWorld();
	void				DeletePhyWorld();

	b2World*			GetWolrd(){ return m_World; }
	ContactListener*	GetContact(){ return m_Contact; }
	
	void				Tick(float dt);
	void				LowTick();

private:
	typedef std::map<int, Game*> GameList;
	typedef std::map<int, GameRoom*> RoomList;
	GameList			m_GameList;
	RoomList			m_RoomList;
	int					m_MakeRoomNum;

	b2World*			m_World;
	ContactListener*	m_Contact;

};

extern GameManager* GGameManager;