#include "pch.h"
#include "CharacterSelectLayer.h"
#include "TcpClient.h"
#include <map>

bool CharacterSelectLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    //선택한 캐릭터 띄울 얼굴추가
    //MakeFaceSprite("Images/SelectFace/[Select]Magician.png", Vec2(winSize.width * 1 / 8, winSize.height * 3 / 4),Vec2(1.0f, 1.0f), Vec2(0,1),HERO_MAGICIAN);
    //MakeFaceSprite("Images/SelectFace/[Select]Jupiter.png", Vec2(winSize.width * 1 / 8, winSize.height * 3 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_JUPITER);

    // 캐릭터 선택창버튼 초상화 추가 (width 1/8씩 ++)
    //auto magicanFace = MenuItemImage::create("Images/SelectFace/[Select]Magician.png", "Images/SelectFace/[Select]Magician_selected.png", CC_CALLBACK_0(CharacterSelectLayer::ClickMagician, this));
    //SetFaceProperty(magicanFace, Vec2(winSize.width * 1 / 8, winSize.height * 1 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1));
    //auto jupiterFace = MenuItemImage::create("Images/SelectFace/[Select]Jupiter.png","Images/SelectFace/[Select]Jupiter_selected.png", CC_CALLBACK_0(CharacterSelectLayer::ClickJupiter, this));
    //SetFaceProperty(jupiterFace, Vec2(winSize.width * 2 / 8, winSize.height * 1 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1));
    //
    //auto faceTable = Menu::create(magicanFace, jupiterFace, NULL);
    //faceTable->setPosition(winSize.width * 1 / 8, winSize.height * 2/8);
    //this->addChild(faceTable);

    //m_CurHero = HERO_MAGICIAN;
    //m_Facelist[HERO_MAGICIAN]->setVisible(true);
    return true;
}

//void CharacterSelectLayer::MakeFaceSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor, HeroType hero)
//{
//   Sprite* sprite = Sprite::create(image);
//   sprite->setPosition(pos);
//   sprite->setScale(scale.x, scale.y);
//   sprite->setAnchorPoint(anchor);
//   sprite->setVisible(false);
//   m_Facelist[hero] = sprite;
//   this->addChild(sprite); 
// }
//
//void CharacterSelectLayer::SetFaceProperty(MenuItemImage* img,Vec2 pos, Vec2 scale, Vec2 anchor)
//{
//    img->setPosition(pos);
//    img->setScale(scale.x, scale.y);
//    img->setAnchorPoint(anchor);
//}
//
//void CharacterSelectLayer::ChangeSelectedHero()
//{
//    switch (m_CurHero)
//    {
//    case HERO_MAGICIAN:
//        for (auto& select : m_Facelist)
//        {
//            select.second->setVisible(false);
//            if (select.first == HERO_MAGICIAN)
//            {
//                select.second->setVisible(true);
//            }
//        }
//        break;
//    case HERO_JUPITER:
//        for (auto& select : m_Facelist)
//        {
//            select.second->setVisible(false);
//            if (select.first == HERO_JUPITER)
//            {
//                select.second->setVisible(true);
//            }
//        }
//        break;
//    case HERO_NONE:
//        break;
//    }
//}
//
//void CharacterSelectLayer::ClickMagician()
//{
//    m_CurHero = HERO_MAGICIAN;
//    ChangeSelectedHero();
//}
//void CharacterSelectLayer::ClickJupiter()
//{
//    m_CurHero = HERO_JUPITER;
//    ChangeSelectedHero();
//}