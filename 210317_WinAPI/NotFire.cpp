#include "NotFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void NotFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;
    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            lpMissile->SetType(Missile::SKILLTYPE::NotSkill_TYPE);
            (this->collisionCheck)->SetBossMissile(lpMissile);
        }
    }
}