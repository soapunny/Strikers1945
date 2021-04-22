#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;
 //   for (int j = 0; j < 5; j++)
    
        //지그재그 아래로 향하는 미사일 장전
        for (int i =0;i<vMissiles->size();i++)
        {
            if ((*vMissiles)[i]->GetIsFired() == false) //난수로써 활용하기로함
            {
                (*vMissiles)[i]->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
                (*vMissiles)[i]->SetIsFired(true);
                (*vMissiles)[i]->SetAngle(DegToRad(a*3));//각각의 각도설정
                 
                break;   
            }
        a++;
        }
    
}
