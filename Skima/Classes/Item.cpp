#include "pch.h"
#include "Item.h"
#include "GameManager.h"
#include "ObjectLayer.h"


Item::Item(Vec2 createPos, float scale, BuffTarget buffType)
{
    m_UnitType = UNIT_ITEM;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    switch (buffType)
    {
    case BUFF_HP:
        m_RealSprite = Sprite::create("Images/Unit/item_hp.png");
        break;
    case BUFF_DAMAGE:
        m_RealSprite = Sprite::create("Images/Unit/item_damage.png");
        break;
    case BUFF_COOLTIME:
        m_RealSprite = Sprite::create("Images/Unit/item_cooltime.png");
        break;
    case BUFF_SHIELD:
        m_RealSprite = Sprite::create("Images/Unit/item_shield.png");
        break;
    case BUFF_SPEED:
        m_RealSprite = Sprite::create("Images/Unit/item_speed.png");
        break;
    }
    m_RealSprite->setScale(scale);
    m_CenterSprite->addChild(m_RealSprite);
}


Item::~Item()
{
}
