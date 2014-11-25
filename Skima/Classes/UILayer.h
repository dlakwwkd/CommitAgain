#pragma once
#include "Enums.h"
#include "PacketType.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UILayer);

	void	Tick(float dt);

	void	CursorChange(CursorMode cursormode);
	void	SetSkillUse(SkillKey key, bool skillOn);
	void	ClickExit(Ref* sender);
	void	loadingMessage();
	void	UpdateHpBar(float curHp, float maxHp);

	Sprite*	GetCurrentShape() { return m_CursorShape; }

private:
	Sprite* m_CursorShape;
	Sprite* m_CursorDefault;
	Sprite* m_CursorAttack;

	Sprite* m_Q_Skill_black;
	bool	m_Q_Skill_On;

};

