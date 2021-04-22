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
    for (int  i =0;i<vMissiles->size();i++)
    {
        if ((*vMissiles)[i]->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*vMissiles)[i]->SetType(Missile::SKILLTYPE::TwoSKill_TYPE);
            (*vMissiles)[i]->SetIsFired(true);
            (*vMissiles)[i]->SetAngle(DegToRad(k));
            
            i++;
            if(i >= 2)
                break;
            
        }

         k+=20;
        if (k > -80) k = -100;
    }
}