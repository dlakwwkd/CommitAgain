#include "LoadingBGLayer.h"
#include "TcpClient.h"


bool LoadingBGLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //������ ����
	{
		return false;
	}
	this->setOpacity(210);

	m_IsLoadingFin = false;

	auto loadingLabel = LabelTTF::create("Loading...", "Arial", 50);
	loadingLabel->setPosition(500, 400);
	this->addChild(loadingLabel);

	this->schedule(schedule_selector(LoadingBGLayer::Tick), 1.0f);
	return true;
}

void LoadingBGLayer::Tick(float dt)
{
	if (m_IsLoadingFin)
	{
		TcpClient::getInstance()->meReadyRequest();
		m_IsLoadingFin = false;
	}
}