#include "FireworkFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void FireworkFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{

    vector<Missile*>::iterator it;
    int fireCnt = 10;
    int initFireCnt = 10;

    for (it = vMissiles->begin(); it != vMissiles->end(); it++)
    {
        if ((*it)->GetIsFired() == false)
        {
            (*it)->SetType(Missile::SKILLTYPE::FIREWORK_TYPE);

            (*it)->SetLpTargetPos(targetPos);
            (*it)->SetAngle(DegToRad(360/initFireCnt * (fireCnt - 1)));
            
            (*it)->SetIsFired(true);
            fireCnt--;
            if (fireCnt <= 0) break;
        }
    }
}
