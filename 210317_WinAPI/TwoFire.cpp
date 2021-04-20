#include "TwoFire.h"
#include "Missile.h"
#include <ctime>
#include "CollisionCheck.h"
void TwoFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));

    int i = 0;
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::TwoSKill_TYPE);
            (*myIt)->SetIsFired(true);            
            (*myIt)->SetAngle(DegToRad(k));
            
            i++;
            if(i >= 2)
                break;
            
        }

         k+=20;
        if (k > -80) k = -100;
    }
}