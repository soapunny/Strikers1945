#include "FireworkFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void FireworkFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{

    int fireCnt = 10;
    int initFireCnt = 10;

    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::FIREWORK_TYPE);

            lpMissile->SetLpTargetPos(targetPos);
            lpMissile->SetAngle(DegToRad(360/initFireCnt * (fireCnt - 1)));
            
            lpMissile->SetIsFired(true);
            fireCnt--;
            if (fireCnt <= 0) break;
        }
    }
}
