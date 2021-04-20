#include "TargetFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void TargetFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;
    //   for (int j = 0; j < 5; j++)

           //지그재그 아래로 향하는 미사일 장전
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            (*myIt)->SetType(Missile::SKILLTYPE::TargetSkill_TYPE);
            (*myIt)->SetIsFired(true);
            (*myIt)->SetAngle(DegToRad(-90));//각각의 각도설정
            (*myIt)->SetMoveSpeed(100 * (a+1));            
            a++;
            if (a == 3)
            {
                a = 0;
                break;
            }
        }

    }

}