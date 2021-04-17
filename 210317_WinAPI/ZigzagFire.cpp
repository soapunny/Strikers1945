#include "ZigzagFire.h"
#include "Missile.h"
void ZigzagFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;
    for (int j = 0; j < 5; j++)
    {
        //지그재그 아래로 향하는 미사일 장전
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::ZigzagSkillTYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(-45);//각각의 각도설정
                break;
            }
        }
    }
}
