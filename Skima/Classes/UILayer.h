#pragma once
#include "Enums.h"
#include "PacketType.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(UILayer);

    void    CursorChange(CursorMode cursorMode);
    void    HideCooltimeBox(SkillKey key);
    void    ClickExit(Ref* sender);
    void    LoadingMessage();
    void    UpdateHpBar(float curHp, float maxHp);

    Sprite* GetCurrentCursor() { return m_Cursor; }
    Sprite* GetCooltimeBox(SkillKey key);

private:
    Sprite* MakeSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor);
    Sprite* MakeCooltimeBox(SkillKey key, Vec2 pos);
    Sprite* MakeCursor(CursorMode mode, const char* image, Vec2 scale, Vec2 anchor);

private:
    Sprite*                         m_Cursor;
    std::map<CursorMode, Sprite*>   m_CursorShape;
    std::map<SkillKey, Sprite*>     m_CooltimeBox;
};

