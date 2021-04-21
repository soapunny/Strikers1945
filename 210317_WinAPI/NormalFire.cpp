#include "NormalFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void NormalFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    vector<Missile*>::iterator myIt;
   // for (int j = 0; j < 5; j++)
    {
        //������ �Ʒ��� ���ϴ� �̻��� ����
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
