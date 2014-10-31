#pragma once
#include <vector>

class GameRoom
{
public:
	GameRoom(int id) : m_RoomID(id){}
	~GameRoom(){}

	int		GetRoomID(){ return m_RoomID; }
	void	JoinPlayer(int id){ m_PlayerIdList.push_back(id); }
	void	OutPlayer(int id);

private:
	int					m_RoomID;
	std::vector<int>	m_PlayerIdList;
};

