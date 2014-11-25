#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();

	int GetCoolTime() { return m_CoolTime; }
	int GetCanUse() { return m_CanUse; }

	void SetCanUse(bool isUse) { m_CanUse = isUse; }

protected:
	int		m_CoolTime;
	bool	m_CanUse;
};

