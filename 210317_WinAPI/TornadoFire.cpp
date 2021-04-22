#include "TornadoFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void TornadoFire::DoFire(CollisionCheck* collisionCheck,vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    //지그재그 아래로 향하는 미사일 장전
    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(a * 20));//각각의 각도설정
            (this->collisionCheck)->SetBossMissile(lpMissile);
            a++;
            break;
        }
    }
}