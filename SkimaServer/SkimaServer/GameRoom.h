#pragma once
#include <vector>
#include <map>

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
	GameRoom(int id) : m_RoomID(id), m_JoinAble(true), m_ReadyNum(0), m_IsAllReady(false)
	{
	}
	~GameRoom(){}

	int								GetRoomID(){ return m_RoomID; }
	PlayerList*						GetPlayerList(){ return &m_PlayerList; }
	bool							IsJoinAble(){ return m_JoinAble; }
	bool							IsAllReady(){ return m_IsAllReady; }
	void							InitReady(){ m_IsAllReady = false; }
	
	void							ReadySign();
	void							JoinPlayer(int id);
	void							OutPlayer(int id);

private:
	PlayerList			m_PlayerList;
	int					m_RoomID;
	int					m_ReadyNum;
	bool				m_JoinAble;
	bool				m_IsAllReady;
};

