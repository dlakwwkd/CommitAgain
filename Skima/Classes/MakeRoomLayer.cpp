#include "pch.h"
#include "MakeRoomLayer.h"
#include "PacketType.h"
#include "TcpClient.h"

#define GET_MAXPLAYER_LABEL dynamic_cast<Label*>(this->getChildByName("MaxPlayerNumLabel"))

bool MakeRoomLayer::init()
{
    if (!Layer::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();

    m_MakeRoomInfo.mMaxPlayerNum = 2;

    auto _bg = MenuItemImage::create("Images/BlackBG.png", "Images/BlackBG.png");
    _bg->setOpacity(210);
    auto bg = Menu::create(_bg, NULL);
    bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(bg);

    auto frame = Sprite::create("Images/MakeRoomFrame.png");
    frame->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(frame, 1);

    auto label = Label::create("2Έν", "Arial", 40);
    frame->addChild(label, 2, "MaxPlayerNumLabel");
    auto rightButton = MenuItemImage::create("Images/RightSelect.PNG", "Images/RightSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::UpMaxPlayerNum, this));
    auto leftButton = MenuItemImage::create("Images/LeftSelect.PNG", "Images/LeftSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::DownMaxPlayerNum, this));
    auto menu1 = Menu::create(rightButton, leftButton, NULL);
    menu1->alignItemsHorizontally();
    frame->addChild(menu1);

    auto VSMode = MenuItemImage::create("Images/VSMode.png", "Images/VSMode.png");
    auto BossMode = MenuItemImage::create("Images/BossMode.png", "Images/BossMode.png");
    auto VSModeSelect = Sprite::create("Images/RoomModeSelect.png");
    VSModeSelect->setVisible(false);
    auto BossModeSelect = Sprite::create("Images/RoomModeSelect.png");
    BossModeSelect->setVisible(false);
    VSMode->addChild(VSModeSelect, 1, "VSSelect");
    BossMode->addChild(BossModeSelect, 1, "BossSelect");

    auto menu2 = Menu::create(VSMode, BossMode, NULL);
    menu2->alignItemsVertically();
    frame->addChild(menu2);

    //auto createRoomButton = MenuItemImage::create("Images/CreateButton.png", "Images/CreateButton_selected.png",
    //    CC_CALLBACK_0(MakeRoomLayer::menuCallback1, this));

    //auto menu3 = Menu::create(createRoomButton, NULL);
    //menu3->setScale(1.3f);
    //menu3->setPosition(Vec2(winSize.width * 0.9f, winSize.height*0.2f));
    //menu3->alignItemsVertically();
    //this->addChild(menu3);

}

void MakeRoomLayer::UpMaxPlayerNum()
{
    if (++m_MakeRoomInfo.mMaxPlayerNum > 8)
        m_MakeRoomInfo.mMaxPlayerNum = 8;

    char buf[4];
    _itoa(m_MakeRoomInfo.mMaxPlayerNum, buf, 10);
    std::string maxPlayerNumStr = buf;
    maxPlayerNumStr += "Έν";

    GET_MAXPLAYER_LABEL->setString(maxPlayerNumStr);
}

void MakeRoomLayer::DownMaxPlayerNum()
{
    if (--m_MakeRoomInfo.mMaxPlayerNum < 2)
        m_MakeRoomInfo.mMaxPlayerNum = 2;

    char buf[4];
    _itoa(m_MakeRoomInfo.mMaxPlayerNum, buf, 10);
    std::string maxPlayerNumStr = buf;
    maxPlayerNumStr += "Έν";

    GET_MAXPLAYER_LABEL->setString(maxPlayerNumStr);
}
