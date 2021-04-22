#include "NormalFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void NormalFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    //일직선 아래로 향하는 미사일 장전
    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::NormalSkill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(-90));
            break;
        }
    }
}
