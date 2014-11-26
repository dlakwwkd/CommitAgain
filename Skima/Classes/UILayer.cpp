#include "pch.h"
#include "UILayer.h"
#include "TcpClient.h"
#include "PacketType.h"

#define SKILLBLACK_WIDTHSCALE 0.03f
#define SKILLBLACK_HIGHTSCALE 0.033f

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto menuItem1 = MenuItemImage::create(	"Images/Exit.png","Images/Exit_selected.png",
		CC_CALLBACK_1(UILayer::ClickExit, this));
	menuItem1->setScale(0.3f, 0.3f);

	auto interfaceimage = Sprite::create("Images/interface.png");
	interfaceimage->setPosition(Point(400, 95));
	interfaceimage->setScale(1.03f, 1.03f);
	this->addChild(interfaceimage);

	auto HpBar = Sprite::create("Images/HpBar_interface.png");
	HpBar->setPosition(Point(400, 88));
	HpBar->setScaleX(0.68f);
	HpBar->setScaleY(1.03f);
	HpBar->setAnchorPoint(Point(0, 0));
	this->addChild(HpBar,10,"HpBar");

	auto fireball = Sprite::create("Images/fireball.jpg");
	fireball->setPosition(Point(443, 38));
	fireball->setScale(0.03f, 0.033f);
	this->addChild(fireball);

	auto iceball = Sprite::create("Images/iceball.jpg");
	iceball->setPosition(Point(518, 38));
	iceball->setScale(0.55f, 0.8f);
	this->addChild(iceball);
	
	m_Q_Skill_Black = Sprite::create("Images/black.jpg");
	m_Q_Skill_Black->setAnchorPoint(Point(0, 0));
	m_Q_Skill_Black->setPosition(Point(413, 8));
	m_Q_Skill_Black->setScale(SKILLBLACK_WIDTHSCALE, SKILLBLACK_HIGHTSCALE);
	m_Q_Skill_Black->setOpacity(200);
	this->addChild(m_Q_Skill_Black);

	m_W_Skill_Black = Sprite::create("Images/black.jpg");
	m_W_Skill_Black->setAnchorPoint(Point(0, 0));
	m_W_Skill_Black->setPosition(Point(490, 8));
	m_W_Skill_Black->setScale(SKILLBLACK_WIDTHSCALE, SKILLBLACK_HIGHTSCALE);
	m_W_Skill_Black->setOpacity(200);
	this->addChild(m_W_Skill_Black);

	auto winSize = Director::getInstance()->getWinSize();
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(winSize.width -40 , 12);
	this->addChild(menu);

	m_CursorDefault = Sprite::create("Images/mouse_cursor.jpg");
	m_CursorAttack = Sprite::create("Images/attack_cursor.jpg");
	m_CursorDefault->setAnchorPoint(Point(0, 0.9f));
	m_CursorAttack->setAnchorPoint(Point(0, 0.9f));
	this->addChild(m_CursorDefault);
	this->addChild(m_CursorAttack);
	m_CursorAttack->setVisible(false);
	m_CursorShape = m_CursorDefault;

	m_CursorTeleport = Sprite::create("Images/cursor_teleport.png");
	m_CursorTeleport->setScale(0.2, 0.08);
	this->addChild(m_CursorTeleport);
	m_CursorShape = m_CursorTeleport;

	return true;
}

void UILayer::CursorChange(CursorMode cursorMode)
{
	auto reduceWidth = ScaleBy::create(5.0f, 0.0f, 1.0f);
	auto invisible = CallFunc::create(CC_CALLBACK_0(UILayer::InvisibleSkillBlack, this, SKILL_Q));
	auto action = Sequence::create(reduceWidth, invisible, NULL);
	m_Q_Skill_Black->runAction(action);

	switch (cursorMode)
	{
	case CURSOR_DEFAULT:
		m_CursorAttack->setVisible(false);
		m_CursorDefault->setVisible(true);
		m_CursorShape = m_CursorDefault;
		break;
	case CURSOR_ATTACK:
		m_CursorAttack->setVisible(true);
		m_CursorDefault->setVisible(false);
		m_CursorShape = m_CursorAttack;
		break;
	}
}


void UILayer::InvisibleSkillBlack(SkillKey key)
{
	switch (key)
	{
	case SKILL_Q:
		m_Q_Skill_Black->setVisible(false);
		m_Q_Skill_Black->setScale(SKILLBLACK_WIDTHSCALE, SKILLBLACK_HIGHTSCALE);
		break;
	case SKILL_W:
		m_W_Skill_Black->setVisible(false);
		m_W_Skill_Black->setScale(SKILLBLACK_WIDTHSCALE, SKILLBLACK_HIGHTSCALE);
		break;
		break;
	case SKILL_E:
		break;
	case SKILL_R:
		break;
	}
}

void UILayer::ClickExit(Ref* sender)
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
	ShowCursor(true);
}

void UILayer::UpdateHpBar(float curHp, float maxHp)
{
	auto hpBar = dynamic_cast<Sprite*>(this->getChildByName("HpBar"));
	hpBar->setScaleX(0.68f*(curHp / maxHp));
}

Sprite* UILayer::GetSkillBlack(SkillKey key)
{
	switch (key)
	{
	case SKILL_Q:
		return m_Q_Skill_Black;
		break;
	case SKILL_W:
		return m_W_Skill_Black;
		break;
	case SKILL_E:
		break;
	case SKILL_R:
		break;
	}
}
