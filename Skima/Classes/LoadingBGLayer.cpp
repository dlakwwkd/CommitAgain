#include "pch.h"
#include "LoadingBGLayer.h"
#include "TcpClient.h"


bool LoadingBGLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK)) //검은색 세팅
    {
        return false;
    }
    this->setOpacity(210);

    m_IsLoadingFin = false;

    auto label = LabelTTF::create("Loading...", "Arial", 50);
    label->setPosition(500, 400);
    this->addChild(label);

    this->schedule(schedule_selector(LoadingBGLayer::Tick), 1.0f);
    return true;
}

//////////////////////////////////////////////////////////////////////////
void LoadingBGLayer::Tick(float dt)
{
    if (m_IsLoadingFin)
    {
        TcpClient::getInstance()->runCompleteRequest();
        m_IsLoadingFin = false;
    }
}
//////////////////////////////////////////////////////////////////////////
