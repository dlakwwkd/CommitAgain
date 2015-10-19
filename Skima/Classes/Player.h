#pragma once
class Player
{
public:
	Player();
	~Player();

	int			GetPlayerId() const { return m_PlayerId; }
	std::string GetPlayerName() const { return m_PlayerName; }

	void		SetPlayerId(int val) { m_PlayerId = val; }
	void		SetPlayerName(const std::string& val) { m_PlayerName = val; }

private:
	int			m_PlayerId;
	std::string m_PlayerName;
};

