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

	int		GetRoomID(){ return m_RoomID; }
	int		GetPlayerListNum(){ return m_PlayerIdList.size(); }

	const std::vector<int>& GetPlayerList(){ return m_PlayerIdList; } ///# 내부 객체의 참조를 통째로 객체 외부로 넘겨주는거는 구조적으로 좋지 못함.
	
	bool	IsJoinAble(){ return m_JoinAble; }
	bool	IsAllReady(){ return m_IsAllReady; }
	void	InitReady(){ m_IsAllReady = false; }
	
	void	ReadySign();
	void	JoinPlayer(int id);
	void	OutPlayer(int id);


private:
	std::vector<int>	m_PlayerIdList;
	int					m_RoomID;
	bool				m_JoinAble;

	int					m_ReadyNum;
	bool				m_IsAllReady;
};

