#pragma once
#include <vector>

class GameRoom
{
public:
	GameRoom(int id) : m_RoomID(id), m_JoinAble(true), m_ReadyNum(0), m_IsAllReady(false)
	{
		m_PlayerIdList.reserve(2);
	}
	~GameRoom(){}

	int						GetRoomID(){ return m_RoomID; }
	const std::vector<int>& GetPlayerList(){ return m_PlayerIdList; }
	bool					IsJoinAble(){ return m_JoinAble; }
	bool					IsAllReady(){ return m_IsAllReady; }
	void					InitReady(){ m_IsAllReady = false; }
	
	void	ReadySign();
	void	JoinPlayer(int id);
	void	OutPlayer(int id);

private:
	std::vector<int>	m_PlayerIdList;
	int					m_RoomID;
	int					m_ReadyNum;
	bool				m_JoinAble;
	bool				m_IsAllReady;
};

