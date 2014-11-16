#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();


	virtual void ShootSkill(int unitId, b2Vec2 targetPos);
	virtual int GetSkillDamage() { return m_Damage; }


protected:
	int	m_Damage;
	int m_PlayerId;
};

