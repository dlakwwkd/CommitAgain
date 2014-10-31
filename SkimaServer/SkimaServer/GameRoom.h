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
	bool	CheckJoinAble(){ return m_JoinAble; }
	void	JoinPlayer(int id);
	void	OutPlayer(int id);

private:
	int					m_RoomID;
	std::vector<int>	m_PlayerIdList;
	bool				m_JoinAble;
};

