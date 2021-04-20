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
    for (int i = 0; i < 10; i++)
    {

        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                randAngle = (rand() % 168 - 18) * 100;
                (*myIt)->SetType(Missile::SKILLTYPE::WormSKill_TYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(DegToRad(k)/** elapsedTime*1000*/);
                (*myIt)->SetMoveSpeed(100);
                    break;
                
                    
            }
        }
        k -= 12;
        if (k == -330)
            break;
    }
}


