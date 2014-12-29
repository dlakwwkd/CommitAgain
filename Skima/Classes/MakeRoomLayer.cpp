#include "pch.h"
#include "MakeRoomLayer.h"
#include "PacketType.h"
#include "TcpClient.h"

#define GET_MAXPLAYER_LABEL dynamic_cast<Label*>(this->getChildByName("MakeRoomFrame")->getChildByName("MaxPlayerNumLabel"))
#define GET_VSMODE_SPRITE   dynamic_cast<Sprite*>(this->getChildByName("MakeRoomFrame")->getChildByName("VSSelect"))
#define GET_BOSSMODE_SPRITE dynamic_cast<Sprite*>(this->getChildByName("MakeRoomFrame")->getChildByName("BossSelect"))

bool MakeRoomLayer::init()
{
    if (!Layer::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();

    m_MakeRoomInfo.mMaxPlayerNum = 2;

    auto _bg = MenuItemImage::create("Images/Background/BlackBG.png", "Images/Background/BlackBG.png");
    _bg->setOpacity(180);
    auto bg = Menu::create(_bg, NULL);
    bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(bg);

    auto frame = Sprite::create("Images/Interface/MakeRoomFrame.png");
    frame->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(frame, 1, "MakeRoomFrame");

    auto label = Label::create("2Έν", "Arial", 40);
    label->setPosition(Vec2(500.0f, 460.0f));
    frame->addChild(label, 2, "MaxPlayerNumLabel");
    auto leftButton = MenuItemImage::create("Images/Interface/LeftSelect.PNG", "Images/Interface/LeftSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::DownMaxPlayerNum, this));
    auto rightButton = MenuItemImage::create("Images/Interface/RightSelect.PNG", "Images/Interface/RightSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::UpMaxPlayerNum, this));
    auto menu1 = Menu::create(leftButton, rightButton, NULL);
    menu1->setPosition(Vec2(500.0f, 460.0f));
    menu1->alignItemsHorizontallyWithPadding(100.0f);
    frame->addChild(menu1);

    auto VSMode = MenuItemImage::create("Images/Interface/VSMode.png", "Images/Interface/VSMode.png",
        CC_CALLBACK_0(MakeRoomLayer::ChangeRoomMode, this, ROOM_BATTLE));
    auto BossMode = MenuItemImage::create("Images/Interface/BossMode.png", "Images/Interface/BossMode.png",
        CC_CALLBACK_0(MakeRoomLayer::ChangeRoomMode, this, ROOM_BOSS));
    auto VSModeSelect = Sprite::create("Images/Interface/RoomModeSelect.png");
    VSModeSelect->setVisible(false);
    VSModeSelect->setPosition(Vec2(280.0f, 230.0f));
    auto BossModeSelect = Sprite::create("Images/Interface/RoomModeSelect.png");
    BossModeSelect->setVisible(false);
    BossModeSelect->setPosition(Vec2(620.0f, 230.0f));
    frame->addChild(VSModeSelect, 1, "VSSelect");
    frame->addChild(BossModeSelect, 1, "BossSelect");

    auto menu2 = Menu::create(VSMode, BossMode, NULL);
    menu2->setPosition(Vec2(450.0f, 230.0f));
    menu2->alignItemsHorizontallyWithPadding(100.0f);
    frame->addChild(menu2);

    auto makeRoomButton = MenuItemImage::create("Images/Interface/MakeRoomButton.png", "Images/Interface/MakeRoomButton_selected.png",
        CC_CALLBACK_0(MakeRoomLayer::MakeRoom, this));
    auto cancelButton = MenuItemImage::create("Images/Interface/CancelButton.png", "Images/Interface/CancelButton_selected.png",
        CC_CALLBACK_0(MakeRoomLayer::CancelMakeRoom, this));

    auto menu3 = Menu::create(makeRoomButton, cancelButton, NULL);
    menu3->setPosition(Vec2(440.0f, 90.0f));
    menu3->alignItemsHorizontally();
    frame->addChild(menu3);

    return true;
}

void MakeRoomLayer::UpMaxPlayerNum()
{
    if (!this->isVisible())
        return;

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

void MakeRoomLayer::ChangeRoomMode(RoomType roomMode)
{
    m_MakeRoomInfo.mRoomType = roomMode;

    switch (roomMode)
    {
    case ROOM_NONE:
        GET_VSMODE_SPRITE->setVisible(false);
        GET_BOSSMODE_SPRITE->setVisible(false);
        break;
    case ROOM_BATTLE:
        GET_VSMODE_SPRITE->setVisible(true);
        GET_BOSSMODE_SPRITE->setVisible(false);
        break;
    case ROOM_BOSS:
        GET_VSMODE_SPRITE->setVisible(false);
        GET_BOSSMODE_SPRITE->setVisible(true);
        break;
    default:
        break;
    }
}

void MakeRoomLayer::MakeRoom()
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    TcpClient::getInstance()->makeRoomRequest(m_MakeRoomInfo);
}

void MakeRoomLayer::CancelMakeRoom()
{
    this->getParent()->removeChildByName("MakeRoomLayer");
}
