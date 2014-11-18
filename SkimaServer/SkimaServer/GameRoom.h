#pragma once
#include <vector>
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;



class GameRoom
{
public:
	GameRoom(int id) : m_RoomID(id), m_JoinAble(true), m_ReadyNum(0), m_IsAllReady(false)
	{
	}
	~GameRoom(){}

	int								GetRoomID(){ return m_RoomID; }
	const PlayerList&				GetPlayerList(){ return m_PlayerList; } ///< 내부 컬렉션을 외부에서 순회하는 방식은 구조적으로 잘못된 것. 객체지향에 맞지 않음. 
	bool							IsJoinAble(){ return m_JoinAble; }
	bool							IsAllReady(){ return m_IsAllReady; }
	void							InitReady(){ m_IsAllReady = false; }
	
	void							ReadySign();
	void							JoinPlayer(int id, Player* player);
	void							OutPlayer(int id);

private:
	PlayerList			m_PlayerList;
	int					m_RoomID;
	int					m_ReadyNum;
	bool				m_JoinAble;
	bool				m_IsAllReady;
};

