#include "stdafx.h"
#include "LightningPumpkinSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"
#include <time.h>

#define MAX_CALL 8
#define REPEAT_TIME 8
#define CALL_DELAY 400
#define REPEAT_DELAY 100
#define LOWERNUM 100
#define UPPERNUM 1000
#define DEPRECIATE 0.1
#define MODIFYNUM 0.4

LightningPumpkinSkill::LightningPumpkinSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 64;
    m_Scale = Reduce(80.0f);
    m_CallCount = 0;
    m_TaretPos = b2Vec2(-1, -1);
}


LightningPumpkinSkill::~LightningPumpkinSkill()
{
}

void LightningPumpkinSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    //auto client = m_Owner->GetClient();
    //client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
    m_TaretPos = targetPos;

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto posFunc = std::bind(&LightningPumpkinSkill::DoNextAttack, this);
    auto posTimer = new Timer(m_Owner->GetRoomID());
    posTimer->WaitRepeatTimer(CALL_DELAY, MAX_CALL, posFunc);
    game->PushTimer(posTimer);
}

void LightningPumpkinSkill::DoNextAttack()
{
    m_CallCount++;
    auto hero = m_Owner->GetMyHero();
    
    auto dir = GenerateDirection();
    auto nextPos = GenerateNextPos(dir);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&LightningPumpkinSkill::FieldDamage, this, nextPos, m_Scale, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, func);
    game->PushTimer(timer);


    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), m_TaretPos, nextPos, SKILL_R);
    if (m_CallCount == MAX_CALL)
    {
         m_CallCount = 0;
    }
}

b2Vec2 LightningPumpkinSkill::GenerateNextPos(Direction direction)
{
    float rndX = GenerateFloatRandom(m_TaretPos.x)*MODIFYNUM;
    float rndY = GenerateFloatRandom(m_TaretPos.y)*MODIFYNUM;
    
    b2Vec2 nextPos;
    switch (direction)
    {
    case N:     nextPos = b2Vec2(m_TaretPos.x + rndX*DEPRECIATE, m_TaretPos.y + rndY);    break;
    case S:     nextPos = b2Vec2(m_TaretPos.x + rndX*DEPRECIATE, m_TaretPos.y - rndY);    break;
    case W:     nextPos = b2Vec2(m_TaretPos.x - rndX, m_TaretPos.y + rndY*DEPRECIATE);    break;
    case E:     nextPos = b2Vec2(m_TaretPos.x + rndX, m_TaretPos.y + rndY*DEPRECIATE);    break;
    case NE:    nextPos = b2Vec2(m_TaretPos.x + rndX, m_TaretPos.y + rndY);    break;
    case SE:    nextPos = b2Vec2(m_TaretPos.x + rndX, m_TaretPos.y - rndY);    break;
    case SW:    nextPos = b2Vec2(m_TaretPos.x - rndX, m_TaretPos.y - rndY);    break;
    case NW:    nextPos = b2Vec2(m_TaretPos.x - rndX, m_TaretPos.y + rndY);    break;
    }
    return nextPos;
}

float LightningPumpkinSkill::GenerateFloatRandom(float num)
{
    if (num == 0) 
        return 0;

    int gap = UPPERNUM - LOWERNUM;
    int toInt = rand() % gap + LOWERNUM;

    int randomInt = rand() % (int)(num * toInt);
    float randomFloat = (float)randomInt / toInt;

    return randomFloat;
}

Direction LightningPumpkinSkill::GenerateDirection()
{
    Direction dir;
    int rnd = rand() % 8;

    switch (rnd)
    {
    case 0: dir = N;  break;
    case 1: dir = S;  break;
    case 2: dir = W;  break;
    case 3: dir = E;  break;
    case 4: dir = NE;  break;
    case 5: dir = SE;  break;
    case 6: dir = SW;  break;
    case 7: dir = NW;  break;

    }
    return dir; 
}
