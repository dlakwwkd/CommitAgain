#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();


	virtual void SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos) = 0;
	virtual int GetSkillDamage() { return m_Damage; }


protected:
	int	m_Damage;
	int m_PlayerId;
	float m_HeroBodySize;
};

