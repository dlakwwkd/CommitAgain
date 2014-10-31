#pragma once
#include <vector>

class GameRoom
{
public:
	GameRoom(int id) : m_RoomID(id), m_JoinAble(true)
	{
		m_PlayerIdList.reserve(2);
	}
	~GameRoom(){}

	int		GetRoomID(){ return m_RoomID; }
	int		GetPlayerListNum(){ return m_PlayerIdList.size(); }
	bool	CheckJoinAble(){ return m_JoinAble; }

	void	JoinPlayer(int id);
	void	OutPlayer(int id);

private:
	std::vector<int>	m_PlayerIdList;
	int					m_RoomID;
	bool				m_JoinAble;
};

