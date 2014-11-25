#pragma once

class Hero;

class Skill
{
public:
	Skill();
	Skill(Hero* hero);
	virtual ~Skill();

	int				GetCoolTime() { return m_CoolTime; }
	int				GetCanUse() { return m_CanUse; }

	void			SetCanUse(bool isUse) { m_CanUse = isUse; }

	virtual void	SkillReady();
	virtual void	SkillEnd();

protected:
	Hero*	m_Hero;

	int		m_CoolTime;
	bool	m_CanUse;
};

