#pragma once
#include "Enums.h"
#include "PacketType.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UILayer);

	void	CursorChange(CursorMode cursormode);
	void	InvisibleSkillBlack(SkillKey key);
	void	ClickExit(Ref* sender);
	void	LoadingMessage();
	void	UpdateHpBar(float curHp, float maxHp);

	Sprite*	GetCurrentShape() { return m_CursorShape; }
	Sprite* GetQSkillBlack() { return m_Q_Skill_black; }

private:
	Sprite* m_CursorShape;
	Sprite* m_CursorDefault;
	Sprite* m_CursorAttack;

	Sprite* m_Q_Skill_black;
};

