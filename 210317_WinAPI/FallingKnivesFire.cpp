#include "FallingKnivesFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void FallingKnivesFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    int fireCnt = 12;

    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::FallingKnives_TYPE);
            lpMissile->SetAngle(DegToRad(-30 * fireCnt));

            lpMissile->SetIsFired(true);
            fireCnt--;
            if (fireCnt <= 0) break;
        }
    }
}
