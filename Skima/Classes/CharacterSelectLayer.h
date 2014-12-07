#pragma once
// #include "PacketType.h"
USING_NS_CC;

/*typedef std::map<HeroType,Sprite*> FaceList;*/

class CharacterSelectLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(CharacterSelectLayer);

private:
//     void MakeFaceSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor,HeroType hero);
//     void SetFaceProperty(MenuItemImage* img,Vec2 pos, Vec2 scale, Vec2 anchor);
//     void ChangeSelectedHero();

    void ClickGameStart(); // 준비완료 레이어 추가??
    void ClickGameExit();
//     void ClickMagician();
//     void ClickJupiter();

private:
//     HeroType m_CurHero;
//     FaceList m_Facelist;
// 
//     Sprite* m_MagicianSprite;
//     Sprite* m_JupiterSprite;
};

