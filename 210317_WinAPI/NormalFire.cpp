#include "NormalFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void NormalFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    vector<Missile*>::iterator myIt;
   // for (int j = 0; j < 5; j++)
    {
        //일직선 아래로 향하는 미사일 장전
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::NormalSkill_TYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(DegToRad(-90));
                break;
            }
        }
    }
}
