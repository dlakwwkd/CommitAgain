#include "stdafx.h"
#include "AdrenalineSkill.h"
#include "ClientSession.h"
#include "Player.h"


AdrenalineSkill::AdrenalineSkill(Player* owner)
{
    m_Owner = owner;
}


AdrenalineSkill::~AdrenalineSkill()
{
}

void AdrenalineSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    //hero�� mspeed�� �÷��ش�
    // �ð��� ������ �ٽ� �ӵ��� �����ְ� tcp�� �뺸 ���ֱ�

//     auto hero = m_Owner->GetMyHero();
//     hero->Crashing(false);
// 
//     auto displacement = targetPos - hero->GetBody()->GetPosition();
//     if (displacement.Normalize() < 0.5f)
//     {
//         return;
//     }
//     displacement *= Reduce(1500);
//     hero->GetBody()->SetLinearVelocity(displacement);
// 
//     auto client = m_Owner->GetClient();
//     client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}
