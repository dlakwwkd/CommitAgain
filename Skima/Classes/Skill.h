#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();

	int GetCoolTime() { return m_CoolTime; };

protected:
	int m_CoolTime;
};

