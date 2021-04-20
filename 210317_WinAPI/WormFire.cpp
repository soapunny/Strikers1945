#include "WormFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void WormFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;

    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
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


