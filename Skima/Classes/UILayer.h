#pragma once
#include "Enums.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(UILayer);

	void CursorChange(CursorMode cursormode);
	void ClickExit(Ref* sender);
	void loadingMessage();

	Sprite* GetCurrentShape() { return m_cursor_shape; }

private:
	Sprite* m_cursor_shape;

	Sprite* m_cursor_default;
	Sprite* m_cursor_attack;

};

