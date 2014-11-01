#pragma once
#include <map>

class Game;
class GameRoom;

class GameManager
{
public:
	GameManager() : m_MakeRoomNum(0){}

	GameRoom*	CreateRoom();
	int			SearchRoom();
	void		JoinRoom(int playerId, int roomId);
	void		OutRoom(int playerId, int roomId);

	void		UpdateRoomState();

private:
	typedef std::map<int, Game*> GameList;
	typedef std::map<int, GameRoom*> RoomList;
	GameList	m_GameList;
	RoomList	m_RoomList;

	int			m_MakeRoomNum;
};

extern GameManager* GGameManager;