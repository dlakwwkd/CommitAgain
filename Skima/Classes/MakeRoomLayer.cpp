#include "pch.h"
#include "MakeRoomLayer.h"
#include "PacketType.h"
#include "TcpClient.h"

#define GET_MAX_PLAYER_LABEL     dynamic_cast<Label*>(this->getChildByName(MAKEROOM_LAYER)->getChildByName(MAX_PLAYER_LABEL))
#define GET_MELEE_MODE_SPRITE   dynamic_cast<Sprite*>(this->getChildByName(MAKEROOM_LAYER)->getChildByName(MELEE_SELECT))
#define GET_TEAM_MODE_SPRITE    dynamic_cast<Sprite*>(this->getChildByName(MAKEROOM_LAYER)->getChildByName(TEAM_SELECT))

bool MakeRoomLayer::init()
{
    if (!Layer::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();
    m_MakeRoomInfo.mRoomType = ROOM_MELEE;
    m_MakeRoomInfo.mMaxPlayerNum = 2;


    // 방설정 창 바깥의 음영처리 및 버튼 무효화
    auto _bg = MenuItemImage::create(
        "Images/Background/BlackBG.png",
        "Images/Background/BlackBG.png");
    auto bg = Menu::create(_bg, NULL);
    bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    bg->setOpacity(180);
    this->addChild(bg);


    // 방설정 창 이미지 생성
    auto frame = Sprite::create("Images/Interface/MakeRoomFrame.png");
    frame->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(frame, 1, MAKEROOM_LAYER);

    auto MeleeModeSelect = Sprite::create("Images/Interface/RoomModeSelect.png");
    MeleeModeSelect->setVisible(true);
    MeleeModeSelect->setPosition(Vec2(280.0f, 230.0f));
    frame->addChild(MeleeModeSelect, 1, MELEE_SELECT);

    auto TeamModeSelect = Sprite::create("Images/Interface/RoomModeSelect.png");
    TeamModeSelect->setVisible(false);
    TeamModeSelect->setPosition(Vec2(620.0f, 230.0f));
    frame->addChild(TeamModeSelect, 1, TEAM_SELECT);

    auto label = Label::create("2명", "Arial", 40);
    label->setPosition(Vec2(500.0f, 460.0f));
    frame->addChild(label, 2, MAX_PLAYER_LABEL);


    // 방설정 창에 버튼들 생성
    auto leftButton = MenuItemImage::create(
        "Images/Interface/LeftSelect.PNG",
        "Images/Interface/LeftSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::DownMaxPlayerNum, this));
    auto rightButton = MenuItemImage::create(
        "Images/Interface/RightSelect.PNG",
        "Images/Interface/RightSelect.PNG",
        CC_CALLBACK_0(MakeRoomLayer::UpMaxPlayerNum, this));
    auto menu1 = Menu::create(leftButton, rightButton, NULL);
    menu1->setPosition(Vec2(500.0f, 460.0f));
    menu1->alignItemsHorizontallyWithPadding(100.0f);
    frame->addChild(menu1);

    auto MeleeMode = MenuItemImage::create(
        "Images/Interface/MeleeModeButton.png",
        "Images/Interface/MeleeModeButton.png",
        CC_CALLBACK_0(MakeRoomLayer::ChangeRoomMode, this, ROOM_MELEE));
    auto TeamMode = MenuItemImage::create(
        "Images/Interface/TeamModeButton.png",
        "Images/Interface/TeamModeButton.png",
        CC_CALLBACK_0(MakeRoomLayer::ChangeRoomMode, this, ROOM_TEAM));
    auto menu2 = Menu::create(MeleeMode, TeamMode, NULL);
    menu2->setPosition(Vec2(450.0f, 230.0f));
    menu2->alignItemsHorizontallyWithPadding(100.0f);
    frame->addChild(menu2);

    auto makeRoomButton = MenuItemImage::create(
        "Images/Interface/MakeRoomButton.png",
        "Images/Interface/MakeRoomButton_selected.png",
        CC_CALLBACK_0(MakeRoomLayer::MakeRoom, this));
    auto cancelButton = MenuItemImage::create(
        "Images/Interface/CancelButton.png",
        "Images/Interface/CancelButton_selected.png",
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
    maxPlayerNumStr += "명";

    GET_MAX_PLAYER_LABEL->setString(maxPlayerNumStr);
}

void MakeRoomLayer::DownMaxPlayerNum()
{
    if (--m_MakeRoomInfo.mMaxPlayerNum < 2)
        m_MakeRoomInfo.mMaxPlayerNum = 2;

    char buf[4];
    _itoa(m_MakeRoomInfo.mMaxPlayerNum, buf, 10);
    std::string maxPlayerNumStr = buf;
    maxPlayerNumStr += "명";

    GET_MAX_PLAYER_LABEL->setString(maxPlayerNumStr);
}

void MakeRoomLayer::ChangeRoomMode(RoomType roomMode)
{
    m_MakeRoomInfo.mRoomType = roomMode;

    switch (roomMode)
    {
    case ROOM_MELEE:
        GET_MELEE_MODE_SPRITE->setVisible(true);
        GET_TEAM_MODE_SPRITE->setVisible(false);
        break;
    case ROOM_TEAM:
        GET_MELEE_MODE_SPRITE->setVisible(false);
        GET_TEAM_MODE_SPRITE->setVisible(true);
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
    this->getParent()->removeChildByName(MAKEROOM_LAYER);
}
