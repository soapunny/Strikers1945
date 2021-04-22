#include "WormFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void WormFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));

    float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
    for (int i=0;i<vMissiles->size();i++)
    {
        if ((*vMissiles)[i]->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*vMissiles)[i]->SetType(Missile::SKILLTYPE::WormSKill_TYPE);
            (*vMissiles)[i]->SetIsFired(true);
            (*vMissiles)[i]->SetAngle(DegToRad(k)/** elapsedTime*1000*/);
            k +=10;
            break;
        }
    }
}


