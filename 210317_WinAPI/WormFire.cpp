#include "WormFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void WormFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));

    float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::WormSKill_TYPE);
            (*myIt)->SetIsFired(true);
            (*myIt)->SetAngle(DegToRad(k)/** elapsedTime*1000*/);
            (this->collisionCheck)->SetBossMissile((*myIt));
            k +=10;
            break;
        }
    }
}


